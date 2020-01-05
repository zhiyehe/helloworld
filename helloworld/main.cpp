#pragma execution_character_set("utf-8")
#include <QApplication>
#include <QTextCodec>
#include <QDebug>
#include "mainwindow.h"
#include "workthread.h"
#include "faceprocess.h"
#include "xml.h"

MainWindow *w_ptr;
int main(int argc, char *argv[])
{
    initfaceprocess();
    qDebug()<<"read xml from file...";
    ReadXml();
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);
    MainWindow w;
    w.setFont(QFont("wenquanyi",20,QFont::Normal));
    w.setWindowTitle("显示中文");
    w.show();
    w_ptr= &w;
    workthread *task = new workthread; // (3) 创建一个 WorkThread 对象
    qDebug()<<"线程测试开始:";
    task->start();//启动该线程 (4)
    qDebug()<<"线程测试结束:";

    return a.exec();
}
