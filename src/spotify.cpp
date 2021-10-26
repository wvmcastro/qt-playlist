#include "spotify.hpp"
#include <iostream>
#include "utils.hpp"

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

rest::http_request
makeClientAuthRequest(const std::string& client_id,
                      const std::string& client_secret)
{
    auto client_id_secret_base64 = 
        utils::Base64::Encode(client_id+":"+client_secret);

    std::stringstream id_secret;
    id_secret << "Basic " << client_id_secret_base64;
    
    rest::http_request request(rest::methods::POST);
    request.headers().add("Authorization", id_secret.str());
    request.headers().add("Content-Type", "application/x-www-form-urlencoded");

    rest::json::value body;
    body["grant_type"] = rest::json::value::string("client_credentials");

    request.set_body("grant_type=client_credentials");

    rest::uri_builder uri(spotify::token_endpoint);
    request.set_request_uri(uri.to_uri());
    return request;
}

} // end spotify