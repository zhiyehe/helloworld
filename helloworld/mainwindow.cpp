#pragma execution_character_set("utf-8")
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QTime>
#include <QTimer>
#include <QPen>
#include <QFont>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTime time = QTime::currentTime();
    ui->setupUi(this);
    qDebug()<<"hello start time:  "<<time.hour()<<":"<<time.minute();
    ui->label->show();

    QPainter painter(this);
    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色
    //painter.setPen(QColor(0, 160, 230));

    QPen pen;  // creates a default pen
    pen.setStyle(Qt::DashDotLine);
    pen.setWidth(10);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);
    // 各个点的坐标
    static const QPointF points[4] = {QPointF(300, 300), QPointF(300, 600), QPointF(600, 600), QPointF(600, 300)};
    // 绘制多边形
    painter.drawPolygon(points, 4);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpDate()));
    timer->start(1000);
}

void MainWindow::timerUpDate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->label_2->setText(str);
}

MainWindow::~MainWindow()
{
    delete ui;
}
