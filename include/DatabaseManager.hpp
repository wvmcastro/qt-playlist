#ifndef DATABASE_HPP
#define DATABASE_HPP
#include <iostream>

#include <list>
#include <tuple>
#include <QSql>
#include <QSqlDatabase>

class DatabaseManager
{
public:
    DatabaseManager(const QString& database_path)
    {
        _database = QSqlDatabase::addDatabase("QSQLITE");
        _database.setDatabaseName(database_path);

        if(!_database.open())
            std::cout << "Database connection failed" << "\n";
        else
            std::cout << "Database connection successful" << std::endl;
    }

    bool addTrackToPlaylist(const std::string& track_spotify_id,
                            int* track_local_id=nullptr);
    std::list<std::tuple<int, std::string>> getPlaylistTracks();
    void removeTrackFromPlaylist(int track_id, int playlist_id=_default_playlist_id);

private:
    constexpr static int _default_playlist_id = 1;
    constexpr static char _tracks_table[] = "tracks_table";
    constexpr static char _association_table[] = "track_playlist_association_table";

    QSqlDatabase _database;
    int addTrackToDatabase(const std::string& track_spotifyid);
    bool trackInDatabase(const std::string& track_spotifyid, int* track_local_id=nullptr);
    bool trackInPlaylist(int track_local_id, int playlist_id=_default_playlist_id);
    std::string getTrackSpotifyId(int track_local_id);

    std::list<std::string> getTracks(int playlist_id=_default_playlist_id);
    std::vector<std::string> getTracks(std::vector<int> tracks_ids);

};

#endif // DATABASE_H
