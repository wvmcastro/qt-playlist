#include "TokenManager.hpp"
#include "spotify.hpp"
#include <chrono>

namespace spotify
{


// implements the flow in:
// https://developer.spotify.com/documentation/general/guides/authorization/client-credentials/
void
TokenManager::tokenFlow(void)
{
    std::unique_lock<std::mutex> lk{_exit_cv_mutex};
    while(true)
    {
        auto response =  requestCode();
        setToken(response["access_token"].as_string());
        
        int expires_in = response["expires_in"].as_integer();
        std::chrono::duration<int, std::ratio<1,1>> timeout{expires_in};

        if(_exit_cv.wait_for(lk, timeout) != std::cv_status::timeout)
            break;
    }
}

rest::json::value
TokenManager::requestCode(void)
{
    auto req = makeClientAuthRequest(_client_id, 
                                     _client_secret);
    auto response = _http_client.request(req).get();
    return response.extract_json().get();
}
std::string
TokenManager::token()
{
    std::shared_lock<std::shared_mutex> lk{_token_mutex};
    return std::string{_current_token};
}
void
TokenManager::setToken(const std::string& token)
{
    std::lock_guard<std::shared_mutex> lk{_token_mutex};
    _current_token = token;
}

}