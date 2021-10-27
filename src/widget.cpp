#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui{new Ui::Widget}, 
    _client{"16d2e555452f4761a4d2ca8dc775675e", 
            "779589eddb4f429d9a9e58fed48d3d3d"}
{
    ui->setupUi(this);
    ui->search_lineEdit->setPlaceholderText(QString("music: "));
    ui->listWidget_tracksList->setDisabled(true);
    ui->pushButton_playtrack->setDisabled(true);
}

Widget::~Widget()
{
    delete ui;
}


void
Widget::on_searchButton_clicked()
{
    auto tracks_response = _client.searchTrack(ui->search_lineEdit->text().toStdString());
    ui->listWidget_tracksList->clear();
    ui->pushButton_playtrack->setDisabled(true);
    auto tracks = spotify::SpotifyClient::extractTracksFromSearchResponse(tracks_response);
    listTracks(tracks);
    ui->listWidget_tracksList->setEnabled(true);
}

void
Widget::listTracks(const std::list<spotify::Track>& tracks)
{
    for(auto& track : tracks)
    {
        std::stringstream ss;
        ss << track;
        ui->listWidget_tracksList->addItem(QString::fromStdString(ss.str()));
    }
}


void Widget::on_listWidget_tracksList_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_playtrack->setEnabled(true);
}

