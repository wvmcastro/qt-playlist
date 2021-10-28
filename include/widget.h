#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include <QListWidgetItem>
#include "SpotifyClient.hpp"
#include <QMediaPlayer>
#include <QAudioOutput>

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

    void listTracks(const std::list<spotify::Track>& tracks);

private slots:
    void on_searchButton_clicked();
    void on_listWidget_tracksList_itemClicked(QListWidgetItem *item);
    void on_pushButton_playtrack_clicked();

    void resetState();
    void playFromUrl(const std::string& track_url);

};
#endif // WIDGET_H
