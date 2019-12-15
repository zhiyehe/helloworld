#include "workthread.h"
#include <QDebug>
#include "faceprocess.h"

workthread::workthread()
{
    workCount = 0;
}

void workthread::run()
{
    initfaceprocess();
    while(true)
    {
        workCount++;
        if(workCount>=1000) workCount=0;
        qDebug()<<"workthread"<<workCount;
        sleep(1);//线程 睡眠一秒一次

        faceprocess();
    }
}
