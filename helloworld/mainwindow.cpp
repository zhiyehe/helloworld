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
#include <QCursor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTime time = QTime::currentTime();
    ui->setupUi(this);
    qDebug()<<"hello start time:  "<<time.hour()<<":"<<time.minute();
    QCursor mycur(QPixmap("/data/shubiao.png"));
    QApplication::setOverrideCursor(mycur);
    ui->label->show();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpDate()));
    timer->start(1000);
    this->setCursor(Qt::ArrowCursor);

    statusLabel=new QLabel;
    statusLabel->setText(tr("当前位置"));
    statusLabel->setFixedWidth(220);
    MousePosLabel=new QLabel;
    MousePosLabel->setText(tr(""));
    MousePosLabel->setFixedWidth(300);

    //在QMainWindow的状态栏中加入控件
    statusBar()->addPermanentWidget(statusLabel);
    statusBar()->addPermanentWidget(MousePosLabel);
    //设置窗体追踪鼠标
    this->setMouseTracking(true);
    this->resize(800,1280);

    //face information input
    dialog = new Dialog(this);
    dialog->setModal(false);
    dialog->hide();
    bshowdialog = false;
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

    QString str3 = "Please face the screen";
    ui->label_3->setText(str3);
}

#if 0
void MainWindow::paintFaceRect(QPointF lefttop, int width, int height)
{
    QPainter painter(this);
    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色、宽度
    painter.setPen(QPen(QColor(0, 160, 230), 6));
    // 设置画刷颜色
    //painter.setBrush(QColor(255, 160, 90));
    //painter.drawRect(160, 180, 480, 600);
    QPointF tmp = lefttop;
    painter.drawLine(tmp, tmp.setY(tmp.y() + 40));
    tmp = lefttop;
    painter.drawLine(tmp, tmp.setX(tmp.x() + 40));

    QPointF tmp2 = lefttop + QPointF(width, 0);
    painter.drawLine(tmp2, tmp2.setX(tmp.x() - 40));
    tmp2 = lefttop + QPointF(width, 0);
    painter.drawLine(tmp2, tmp2.setY(tmp.y() + 40));

    QPointF tmp3 = lefttop + QPointF(0, height);
    painter.drawLine(tmp3, tmp3.setY(tmp.y() - 40));
    tmp3 = lefttop + QPointF(0, height);
    painter.drawLine(tmp3, tmp3.setX(tmp.x() + 40));

    QPointF tmp4 = lefttop + QPointF(width, height);
    painter.drawLine(tmp4, tmp4.setY(tmp.y() - 40));
    tmp4 = lefttop + QPointF(width, height);
    painter.drawLine(tmp4, tmp4.setX(tmp.x() - 40));
}
#endif

//mousePressEvent()函数为鼠标按下事件响应函数
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        statusBar()->showMessage(tr("左键"));
    }
    else if(e->button() == Qt::RightButton)
    {
        statusBar()->showMessage(tr("右键"));
    }
    else if(e->button() == Qt::MidButton)
    {
        statusBar()->showMessage(tr("中键"));
    }
}
//mouseMoveEvent()函数为鼠标移动事件响应函数
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    MousePosLabel->setText("("+QString::number(e->x())+","+QString::number(e->y())+")");
}
//mouseReleaseEvent()函数为鼠标松开事件响应函数
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
}
//mouseDoubleClickEvent()函数为鼠标双击事件响应函数
void MainWindow::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
}

void MainWindow::showfacedectetresult(int btrue)
{
    if(btrue == 0)
    {
        QString str2 = "请正对屏幕";
        ui->label->setText(str2);

        QString str3 = "Please face the screen";
        ui->label_3->setText(str3);
    }
    else
    {
        QString str2 = "检测到人脸";
        ui->label->setText(str2);

        QString str3 = "Detect the face";
        ui->label_3->setText(str3);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(not bshowdialog)
    {
        dialog->show();
        bshowdialog = true;
    }
    else
    {
        dialog->hide();
        bshowdialog = false;
    }
}
