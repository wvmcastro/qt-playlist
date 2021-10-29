#ifndef _SPOTIFY_CLIENT_HPP
#define _SPOTIFY_CLIENT_HPP

#include "spotify.hpp"
#include "TokenManager.hpp"
#include <string>
#include <list>

namespace spotify
{

class SpotifyClient
{
public:
    SpotifyClient(const std::string client_id, 
                  const std::string& client_secret): 
        _http_client{api_url}, 
        _token_manager{client_id, client_secret}
    {
        // do nothing
    }

    pplx::task<rest::http_response> searchTrack(const std::string& track_name);
    
    pplx::task<rest::http_response> getTrackSet(const std::list<std::string>& tracks_id);
    
    static std::list<Track> extractTracksFromSearchResponse(
        pplx::task<rest::http_response>& searchResponse);
    static std::list<Track>extractTracksFromSetResponse(
        pplx::task<rest::http_response>& setResponse);

    std::string token()
    {
        return _token_manager.token();
    }

private:
    rest::http_client _http_client;
    TokenManager _token_manager;

    };

}

#endif
