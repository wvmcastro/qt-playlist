#include "SpotifyClient.hpp"

namespace spotify
{
    rest::json::value
    SpotifyClient::searchTrack(const std::string& track_name)
    {
        auto request = makeTrackRequest(track_name, _token);
        
        auto response = _http_client.request(request).get();
        std::cout << response.extract_string().get() << std::endl;
        return response.extract_json().get();
    }
}

