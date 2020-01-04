#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>

class workthread : public QThread
{
public:
    workthread();
private:
    virtual void run();//任务处理线程
public:
    int workCount;//计数

signals:

public slots:

};
#endif // WORKTHREAD_H
