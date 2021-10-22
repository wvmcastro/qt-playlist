#ifndef _SPOTIFY_CLIENT_HPP
#define _SPOTIFY_CLIENT_HPP

#include "spotify.hpp"
#include <string>

namespace spotify
{

class SpotifyClient
{
public:
    SpotifyClient(const std::string token): _token{token},
        _http_client{api_url}
    {
        // do nothing
    }

    rest::json::value searchTrack(const std::string& track_name);

private:
    std::string _token;
    rest::http_client _http_client;
};

}

#endif