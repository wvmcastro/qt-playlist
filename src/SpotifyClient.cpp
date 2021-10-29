#include "SpotifyClient.hpp"

namespace spotify
{
pplx::task<rest::http_response>
SpotifyClient::searchTrack(const std::string& track_name)
{
    auto request = makeTrackSearchRequest(track_name, token());
    
    return _http_client.request(request);
}

pplx::task<rest::http_response>
SpotifyClient::getTrackSet(const std::list<std::string>& tracks_id)
{
    auto request = makeTrackSetRequest(tracks_id, token());
    return _http_client.request(request);
}

std::list<Track>
SpotifyClient::extractTracksFromSearchResponse(
    pplx::task<rest::http_response>& searchResponse)
{
    auto resp = searchResponse.get();
    if(resp.status_code() != 200) // NOT OK
        return std::list<Track>{};

    auto resp_data = resp.extract_json().get();
    auto tracks_array = resp_data.at("tracks").at("items").as_array();

    std::list<Track> tracks_list;
    for(auto& track : tracks_array)
    {
        if(track.at("preview_url").is_string() == true)
            tracks_list.push_back(Track::makeTrackFromJsonData(track));
    }
    return tracks_list;
}

std::list<Track>
SpotifyClient::extractTracksFromSetResponse(
    pplx::task<rest::http_response>& setResponse)
{
    auto resp = setResponse.get();
    if(resp.status_code() != 200) // NOT OK
        return std::list<Track>{};

    auto resp_data = resp.extract_json().get();
    auto tracks_array = resp_data.at("tracks").as_array();

    std::list<Track> tracks_list;
    for(auto& track : tracks_array)
    {
        tracks_list.push_back(Track::makeTrackFromJsonData(track));
    }
    return tracks_list;
}

}

