#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
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

private slots:
    void on_searchButton_clicked();
};
#endif // WIDGET_H
