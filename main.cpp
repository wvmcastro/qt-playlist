#include <QApplication>
#include "widget.h"
#include "SpotifyClient.hpp"

constexpr char dev_token[] = "token";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
