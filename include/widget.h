#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include "SpotifyClient.hpp"

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
    spotify::SpotifyClient _client;

    void listTracks(const std::list<spotify::Track>& tracks);

private slots:
    void on_searchButton_clicked();
    void on_listWidget_tracksList_itemClicked(QListWidgetItem *item);
};
#endif // WIDGET_H
