#include "dialog.h"
#include "ui_dialog.h"
#include "xml.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    qDebug()<<"snap the img";
}

void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    qDebug()<<"save the information to xml";
    qDebug()<<"write xml to file...";
    WriteXml();
}
