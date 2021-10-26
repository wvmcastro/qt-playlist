#ifndef _TOKEN_MANAGER_CPP
#define _TOKEN_MANAGER_CPP

#include "spotify.hpp"
#include <string>
#include <thread>
#include <shared_mutex>
#include <condition_variable>

namespace spotify
{

class TokenManager
{
public:
    TokenManager(const std::string& client_id, const std::string& client_secret): 
    _client_id{client_id}, _client_secret{client_secret},
    _http_client{token_api_url},
    _th{&TokenManager::tokenFlow, this}
    {
        // do nothing
    }

    ~TokenManager()
    {
        _exit_cv.notify_one();
        _th.join();
    }
    
    std::string token();
private:
    std::thread _th;
    mutable std::shared_mutex _token_mutex;
    std::mutex _exit_cv_mutex;
    std::condition_variable _exit_cv;

    std::string _current_token;
    std::string _client_id;
    std::string _client_secret;
    rest::http_client _http_client;

    void tokenFlow(void);
    rest::json::value requestCode(void);
    void setToken(const std::string& token);
};

}
#endif