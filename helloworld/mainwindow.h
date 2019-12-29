#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStatusBar>
#include <QMouseEvent>
#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void timerUpDate();

    void on_pushButton_clicked();

public:
    explicit MainWindow(QWidget *parent = 0);
    void showfacedectetresult(int btrue);
    //void paintFaceRect(QPointF lefttop, int width, int height);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    //重定义了QWidget类的鼠标事件方法
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);

private:
    Ui::MainWindow *ui;
    QLabel *statusLabel;
    QLabel *MousePosLabel;
    Dialog *dialog;
};

#endif // MAINWINDOW_H
