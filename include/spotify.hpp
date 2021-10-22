#ifndef _SPOTIFY_HPP
#define _SPOTIFY_HPP

#include "rest.hpp"
#include <string>

namespace spotify
{

inline constexpr char api_url[] = "https://api.spotify.com";
inline constexpr char search_endpoint[] = "/v1/search";

rest::http_request
makeTrackRequest(const std::string& track_name, 
                 const std::string& token, 
                 int limit=5);

} // end spotify

#endif