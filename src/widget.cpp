#include "widget.h"
#include "ui_widget.h"
#include <iterator>
#include <tuple>
#include "config.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui{new Ui::Widget}, 
    _client{APPID, APPSECRET},
    _player{new QMediaPlayer(this)}, _audio_output{new QAudioOutput(this)},
    _database(DATABASEPATH)
{
    ui->setupUi(this);
    _player->setAudioOutput(_audio_output);
    ui->search_lineEdit->setPlaceholderText(QString("music: "));

    resetState();
    ui->pushButton_playlistplayback->setDisabled(true);
    ui->pushButton_removefromplaylist->setDisabled(true);

    loadPlaylistView();
}

Widget::~Widget()
{
    delete ui;
    delete _player;
    delete _audio_output;
}


void
Widget::loadPlaylistView()
{
    _last_playlist_query = _database.getPlaylistTracks();

    std::list<std::string> tracks_spotify_id;
    for(auto& tuple : _last_playlist_query)
        tracks_spotify_id.push_back(std::get<1>(tuple));

    if(tracks_spotify_id.size() == 0)
        return;

    auto track_set_response = _client.getTrackSet(tracks_spotify_id);

    auto tracks = spotify::SpotifyClient::extractTracksFromSetResponse(
                track_set_response
                );
    listTracks(tracks, ui->listWidget_playlist);
}

void
Widget::reloadPlayListView()
{
    ui->listWidget_playlist->clear();
    loadPlaylistView();
}

void
Widget::listTracks(const std::list<spotify::Track>& tracks, QListWidget* list)
{
    for(auto& track : tracks)
        addTrackViewToListWidget(track, list);
}

inline void
Widget::addTrackViewToListWidget(const spotify::Track track, QListWidget* list)
{
    std::stringstream ss;
    ss << track;
    list->addItem(QString::fromStdString(ss.str()));
}

void
Widget::resetState()
{
    ui->listWidget_tracksList->clear();
    ui->pushButton_playtrack->setDisabled(true);
    ui->pushButton_playtrack->setDisabled(true);
    ui->pushButton_addtoplaylist->setDisabled(true);
}

void
Widget::playFromUrl(const std::string& track_url)
{
//    std::cout << track_url << std::endl;
//    _player->setActiveAudioTrack(-1);
//    std::cout << "Media status: " << _player->mediaStatus() << std::endl;
//    std::cout << "Active audio track: " << _player->activeAudioTrack() << std::endl;
//    _player->stop();
//    QUrl url{QString::fromStdString(track_url)};
//    _player->setSource(url);
//    _player->setActiveAudioTrack(1);
//    _audio_output->setVolume(50);
//    _player->play();
//    std::cout << "Media status2: " << _player->mediaStatus() << std::endl;
//    std::cout << "player" << std::endl;
}

void Widget::on_pushButton_addtoplaylist_clicked()
{
    int selected_track_index = ui->listWidget_tracksList->currentRow();
    auto track = std::next(_last_search.begin(), selected_track_index);

    int local_id;
    bool added = _database.addTrackToPlaylist(track->spotify_id, &local_id);
    if(added)
    {
        _last_playlist_query.push_back(std::tuple(
                                           local_id,
                                           track->spotify_id
                                           )
                                       );

        addTrackViewToListWidget(*track, ui->listWidget_playlist);

    }
}


void Widget::on_listWidget_playlist_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_removefromplaylist->setEnabled(true);
    ui->pushButton_playlistplayback->setEnabled(true);
}


void Widget::on_pushButton_removefromplaylist_clicked()
{
    int track_row = ui->listWidget_playlist->currentRow();
    auto track = std::next(_last_playlist_query.begin(), track_row);
    int track_local_id = std::get<0>(*track);

    _database.removeTrackFromPlaylist(track_local_id);

    ui->listWidget_playlist->takeItem(track_row);
    _last_playlist_query.erase(track);

    if(ui->listWidget_playlist->count() == 0)
    {
        ui->pushButton_playlistplayback->setDisabled(true);
        ui->pushButton_removefromplaylist->setDisabled(true);
    }
}

void Widget::on_listWidget_tracksList_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_playtrack->setEnabled(true);
    ui->pushButton_addtoplaylist->setEnabled(true);
}


void Widget::on_pushButton_playtrack_clicked()
{
    int selected_track_index = ui->listWidget_tracksList->currentRow();
    auto track = std::next(_last_search.begin(), selected_track_index);
    playFromUrl(track->audio_url);
}

void
Widget::on_searchButton_clicked()
{
    auto tracks_response = _client.searchTrack(ui->search_lineEdit->text().toStdString());
    resetState();
    auto tracks = spotify::SpotifyClient::extractTracksFromSearchResponse(
                tracks_response
                );
    listTracks(tracks, ui->listWidget_tracksList);
    _last_search = tracks;
    ui->listWidget_tracksList->setEnabled(true);
}


