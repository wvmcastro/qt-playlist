#ifndef _SPOTIFY_HPP
#define _SPOTIFY_HPP

#include "rest.hpp"
#include <string>
#include <list>

namespace spotify
{

inline constexpr char api_url[] = "https://api.spotify.com";
inline constexpr char search_endpoint[] = "/v1/search";
inline constexpr char tracks_endpoint[] = "/v1/tracks";

inline constexpr char token_api_url[] = "https://accounts.spotify.com";
inline constexpr char token_endpoint[] = "/api/token";

inline constexpr char market[] = "BR";

rest::http_request
makeTrackSearchRequest(const std::string& track_name,
                 const std::string& token, 
                 int limit=10);

rest::http_request
makeTrackSetRequest(const std::list<std::string>& tracks_id,
                    const std::string& token);

rest::http_request
makeClientAuthRequest(const std::string& client_id,
                      const std::string& client_secret);


struct Track
{
    std::string name;
    std::vector<std::string> artists;
    std::string album;
    std::string spotify_id;
    std::string audio_url;

    static Track makeTrackFromJsonData(const rest::json::value& track_data);
};


std::ostream & operator<<(std::ostream & os, const Track& track);

} // end spotify
#endif
