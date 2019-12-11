#pragma execution_character_set("utf-8")
#include<QApplication>
#include "mainwindow.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);
    MainWindow w;

    w.setFont(QFont("wenquanyi",20,QFont::Normal));
    w.setWindowTitle("显示中文");
    w.show();


    return a.exec();
}
