#include "dialog.h"
#include "ui_dialog.h"
#include "xml.h"
#include <QDebug>
#include <QCoreApplication>
#include <QFile>

bool bGetData = true;
int bmpSize;
unsigned char bmpData[1024*640*3];
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
    bGetData = 1;
    number = ui->textEdit->toPlainText();
    name = ui->textEdit_2->toPlainText();
    filename = name + number +".bmp";
    qDebug()<<"snap the img: "<<filename;
    QFile file(filename);
    if(file.open(QFile::WriteOnly|QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
    {
        file.write((const char*)bmpData, bmpSize); // write to stderr
        file.close();
    }
}

void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    qDebug()<<"save the information to xml";
    qDebug()<<"write xml to file...";
    number = ui->textEdit->toPlainText();
    name = ui->textEdit_2->toPlainText();
    filename = name + number +".bmp";
    WriteXml(name,number);
}
