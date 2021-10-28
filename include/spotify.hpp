#ifndef _SPOTIFY_HPP
#define _SPOTIFY_HPP

#include "rest.hpp"
#include <string>

namespace spotify
{

inline constexpr char api_url[] = "https://api.spotify.com";
inline constexpr char search_endpoint[] = "/v1/search";
inline constexpr char token_api_url[] = "https://accounts.spotify.com";
inline constexpr char token_endpoint[] = "/api/token";

rest::http_request
makeTrackRequest(const std::string& track_name, 
                 const std::string& token, 
                 int limit=5);

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