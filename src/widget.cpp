#include "widget.h"
#include "ui_widget.h"
#include <iterator>
#include <tuple>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui{new Ui::Widget}, 
    _client{"16d2e555452f4761a4d2ca8dc775675e", 
            "779589eddb4f429d9a9e58fed48d3d3d"},
    _player{new QMediaPlayer(this)}, _audio_output{new QAudioOutput(this)},
    _database("/home/wellington/repositories/qt-playlist/dev-env/test.db")
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
    auto tracks_query = _database.getPlaylistTracks();

    std::list<std::string> tracks_spotify_id;
    for(auto& tuple : tracks_query)
        tracks_spotify_id.push_back(std::get<1>(tuple));
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

void
Widget::listTracks(const std::list<spotify::Track>& tracks, QListWidget* list)
{
    for(auto& track : tracks)
    {
        std::stringstream ss;
        ss << track;
        list->addItem(QString::fromStdString(ss.str()));
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
    _database.addTrackToPlaylist(track->spotify_id);
    reloadPlayListView();
}


void Widget::on_listWidget_playlist_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_removefromplaylist->setEnabled(true);
    ui->pushButton_playlistplayback->setEnabled(true);
}

