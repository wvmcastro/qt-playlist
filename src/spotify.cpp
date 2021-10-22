#include "spotify.hpp"
#include <iostream>

namespace spotify
{

rest::http_request
makeTrackRequest(const std::string& track_name, 
                 const std::string& token,
                 int limit)
{
    constexpr char market[] = "BR";
    constexpr char type[] = "track";
    constexpr char content_type[] = "application/json";

    rest::uri_builder uri(spotify::search_endpoint);
    uri.append_query("q", track_name);
    uri.append_query("type", type);
    uri.append_query("market", market);
    uri.append_query("limit", limit);

    rest::http_request request(rest::methods::GET);
    request.set_request_uri(uri.to_uri());
    request.headers().add("Authorization", "Bearer " + token);
    
    return request;
}

} // end spotify