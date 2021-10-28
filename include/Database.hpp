#ifndef DATABASE_HPP
#define DATABASE_HPP
#include <iostream>

#include <list>
#include <QSql>
#include <QSqlDatabase>

class Database
{
public:
    Database(const QString& database_path)
    {
        _database = QSqlDatabase::addDatabase("QSQLITE");
        std::cout << "Drivers: " << _database.driverName().toStdString() << std::endl;
        _database.setDatabaseName(database_path);

        if(!_database.open())
            std::cout << "Database connection failed" << "\n";
        else
            std::cout << "Database connection successful" << std::endl;
        std::cout << _database.connectionName().toStdString() << std::endl;
        std::cout << _database.databaseName().toStdString() << std::endl;;
    }

private:
    constexpr static int _default_playlist_id = 1;
    QSqlDatabase _database;
    std::list<std::string> getTracks(int playlist_id=_default_playlist_id);
    std::vector<std::string> getTracks(std::vector<int> tracks_ids);
    std::vector<int> getTracksIdsFromPlaylist(int playlist_id=_default_playlist_id);
    void addTrackToPlaylist(int track_id, int playlist_id=_default_playlist_id);
    void removeTrackFromPlaylist(int track_id, int playlist_id=_default_playlist_id);
};

#endif // DATABASE_H
