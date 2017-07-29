#include "mainwindow.h"
#include "sh3monitorthread.h"
#include "memory.h"
#include "sh3processing.h"

#include <QtCore>
#include <QDebug>

sh3MonitorThread::sh3MonitorThread()
{

}

void sh3MonitorThread::run(){
    monitor();
}

void sh3MonitorThread::monitor(){

    Memory *MemoryObj = new Memory();
    sh3Processing *sh3ProcessingObj = new sh3Processing();
    while(true){

        if (MemoryObj->sh3IsRunning() && (!sh3ProcessingObj->isRunning())) {
            sh3ProcessingObj->start();
            QThread::sleep(1);

        }
        QThread::sleep(5);
    }
    qDebug() << "";
}
