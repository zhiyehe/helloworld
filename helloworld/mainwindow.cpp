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

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpDate()));
    timer->start(1000);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色、宽度
    painter.setPen(QPen(QColor(0, 160, 230), 6));
    // 设置画刷颜色
    //painter.setBrush(QColor(255, 160, 90));
    //painter.drawRect(160, 180, 480, 600);
    painter.drawLine(QPointF(160, 180), QPointF(160, 220));
    painter.drawLine(QPointF(160, 180), QPointF(200, 180));

    painter.drawLine(QPointF(640, 180), QPointF(600, 180));
    painter.drawLine(QPointF(640, 180), QPointF(640, 220));

    painter.drawLine(QPointF(160, 780), QPointF(160, 740));
    painter.drawLine(QPointF(160, 780), QPointF(200, 780));

    painter.drawLine(QPointF(640, 780), QPointF(640, 740));
    painter.drawLine(QPointF(640, 780), QPointF(600, 780));
}

void MainWindow::timerUpDate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss");
    ui->label_2->setText(str);

    QString str2 = "请正对屏幕";
    ui->label->setText(str2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
