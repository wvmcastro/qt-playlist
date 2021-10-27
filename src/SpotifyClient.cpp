#include "SpotifyClient.hpp"

namespace spotify
{
pplx::task<rest::http_response>
SpotifyClient::searchTrack(const std::string& track_name)
{
    auto request = makeTrackRequest(track_name, token());
    
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
       tracks_list.push_back(Track::makeTrackFromJsonData(track));
    }
    return tracks_list;
}

}

