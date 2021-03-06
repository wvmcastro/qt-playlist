#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include <QListWidgetItem>
#include "SpotifyClient.hpp"
#include <QMediaPlayer>
#include <QAudioOutput>
#include "DatabaseManager.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QMediaPlayer* _player;
    QAudioOutput* _audio_output;

    spotify::SpotifyClient _client;
    std::list<spotify::Track> _last_search;

    DatabaseManager _database;
    std::list<std::tuple<int, std::string>> _last_playlist_query;

    void listTracks(const std::list<spotify::Track>& tracks, QListWidget* list);
    void loadPlaylistView();
    void reloadPlayListView();

private slots:
    void on_searchButton_clicked();
    void on_listWidget_tracksList_itemClicked(QListWidgetItem *item);
    void on_pushButton_playtrack_clicked();

    void resetState();
    void playFromUrl(const std::string& track_url);
    void addTrackViewToListWidget(const spotify::Track track, QListWidget* list);

    void on_pushButton_addtoplaylist_clicked();
    void on_listWidget_playlist_itemClicked(QListWidgetItem *item);
    void on_pushButton_removefromplaylist_clicked();
};
#endif // WIDGET_H
