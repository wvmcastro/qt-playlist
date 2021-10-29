#include "spotify.hpp"
#include <iostream>
#include "utils.hpp"

namespace spotify
{

rest::http_request
makeTrackSearchRequest(const std::string& track_name,
                       const std::string& token,
                       int limit)
{
    constexpr char type[] = "track";

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
makeTrackSetRequest(const std::list<std::string>& tracks_id,
                    const std::string& token)
{
    std::stringstream ss;
    auto last = --tracks_id.end();
    for(auto it = tracks_id.begin(); it != last; it++)
    {
        ss << (*it) << ",";
    }
    ss << (*last);

    rest::uri_builder uri(spotify::tracks_endpoint);
    uri.append_query("market", market);
    uri.append_query("ids", ss.str());

    rest::http_request request(rest::methods::GET);
    request.set_request_uri(uri.to_uri());

    request.headers().add("Authorization", "Bearer " + token);
    constexpr char content_type[] = "application/json";
    request.headers().add("Content-Type", content_type);

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

Track
Track::makeTrackFromJsonData(const rest::json::value& track_data)
{
    Track track;
    track.name = track_data.at("name").as_string();
    track.album = track_data.at("album").at("name").as_string();
    track.spotify_id = track_data.at("id").as_string();
    track.audio_url = track_data.at("preview_url").as_string();

    auto artists_array = track_data.at("artists").as_array();
    for(auto& artist : artists_array)
        track.artists.push_back(artist.at("name").as_string());
    
    return track;
}

std::ostream & operator<<(std::ostream & os, const Track& track)
{
    os << "Name:\t" << track.name << std::endl;
    os << "Album:\t" << track.album << std::endl;

    os << "Artists:\t";
    int n = track.artists.size();
    for(int i = 0; i < n-1; i++)
        os << track.artists[i] << ", ";
    os << track.artists[n-1] << std::endl;

    return os;
}

} // end spotify
