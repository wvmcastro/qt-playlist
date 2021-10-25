#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui{new Ui::Widget}, _client{"token"}
{
    ui->setupUi(this);
    ui->search_lineEdit->setPlaceholderText(QString("música: "));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_searchButton_clicked()
{
   auto result = _client.searchTrack(ui->search_lineEdit->text().toStdString());
   ui->textBrowser->setText(result.serialize().c_str());
}

