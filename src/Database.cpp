#include "Database.hpp"

#include <sstream>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>


bool
Database::addTrackToPlaylist(const std::string& track_spotifyid)
{
    int track_local_id = addTrackToDatabase(track_spotifyid);

    if(trackInPlaylist(track_local_id) == false)
    {
        std::stringstream query_ss;
        query_ss << "INSERT INTO " << _association_table
                 << " (id_track, id_playlist) VALUES ("
                 << track_local_id << ", " << _default_playlist_id << ")";

        QSqlQuery query;
        query.exec(query_ss.str().c_str());
        return true;
    }

    return false;
}

void 
Database::removeTrackFromPlaylist(int track_id, int playlist_id)
{

}

int
Database::addTrackToDatabase(const std::string& track_spotifyid)
{
    int track_local_id;
    if(trackInDatabase(track_spotifyid, &track_local_id))
        return track_local_id;

    std::stringstream query_ss;
    query_ss << "INSERT INTO " << _tracks_table
             << " (track_spotify_id)"
             << " VALUES ('" << track_spotifyid << "')";

    QSqlQuery query;
    query.exec(query_ss.str().c_str());

    query.clear();
    query.exec("SELECT last_insert_rowid()");
    query.first();
    track_local_id = query.value(0).toInt();

    return track_local_id;
}

bool
Database::trackInDatabase(const std::string& track_spotifyid, int* track_local_id)
{
    std::stringstream query_ss;
    query_ss << "SELECT id_track FROM " << _tracks_table
                 << " WHERE track_spotify_id = '" << track_spotifyid << "'";

    QSqlQuery query;
    query.exec(query_ss.str().c_str());

    bool track_in_database = query.first();
    if(track_local_id != nullptr && track_in_database)
        (*track_local_id) = query.value(0).toInt();

    return track_in_database;
}

bool
Database::trackInPlaylist(int track_local_id, int playlist_id)
{
    std::stringstream query_ss;
    query_ss << "SELECT id_track, id_playlist FROM "
             << _association_table << " WHERE "
             << "id_track = " << track_local_id << " AND "
             << "id_playlist = " << playlist_id;

    QSqlQuery query;
    query.exec(query_ss.str().c_str());
    return query.first();
}

std::list<std::tuple<int, std::string>>
Database::getPlaylistTracks()
{
    std::stringstream query_ss;
    query_ss << "SELECT id_track FROM "
             << _association_table << " WHERE "
             << "id_playlist = " << _default_playlist_id;

    std::list<std::tuple<int, std::string>> tracks;

    QSqlQuery query;
    query.exec(query_ss.str().c_str());
    while(query.next())
    {
        int track_local_id = query.value(0).toInt();
        tracks.push_back(std::tuple(track_local_id,
                                    getTrackSpotifyId(track_local_id)
                                    )
                         );
    }
    return tracks;
}

std::string
Database::getTrackSpotifyId(int track_local_id)
{
    std::stringstream query_ss;
    query_ss << "SELECT track_spotify_id FROM "
             << _tracks_table << " WHERE "
             << "id_track = " << track_local_id;

    QSqlQuery query;
    query.exec(query_ss.str().c_str());
    query.first();
    auto id = query.value(0).toString().toStdString();
    return id;
}
