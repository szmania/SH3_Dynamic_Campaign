//Launch the batch file from here

#include "mainwindow.h"
#include "batch.h"
#include "grabdata.h"
#include <QDir>
#include <QProcess>
#include <QString>
#include <QDebug>
#include <QMutex>


Batch::Batch()
{

    //qDebug() << QDir::currentPath();

}

Batch::~Batch(){

}


void Batch::startup() {
//    GrabData *grabData = new GrabData();
    QStringList abc;
    //abc << "/C" << "start" << "/min" << "" << "SH3_Dynamic_Campaign.exe" << "startup" << "^&" << "exit";
    abc << "startup" ;

    //QProcess p;
    //p.startDetached("cmd.exe",abc);
    //abc << "/C";

    QProcess *p = new QProcess;
    //p->start("cmd.exe",abc);
    p->start("SH3_Dynamic_Campaign.exe", abc);

    if(p->waitForStarted()) {
        qDebug() << "SH3_Dynamic_Campaign.exe \"startup\" - executed";
    }
    else {
        qDebug() << "SH3_Dynamic_Campaign.exe \"startup\" - could not start";
    }


    p->waitForFinished();
//    QMutex mut;
//    mut.lock();
//    mut.tryLock(600);
//    mut.unlock();

}

void Batch::submarineTrackingRoom_monitor(){

    QString processName = "Submarine Tracking Room V7.exe";
    QStringList abc;
    abc << "/C" << "start" << "/min" << "" << "SH3_Dynamic_Campaign.exe" << "process_monitor" << processName << "^&" << "exit";
    QProcess *p = new QProcess;
    p->start("cmd.exe", abc);
}


void Batch::sh3DC(QString type, QString career){
    QStringList abc;
    abc << "/C" << "start" << "/min" << "" << "SH3_Dynamic_Campaign.exe" << "dc" << type << career << "^&" << "exit";
    QProcess *p = new QProcess;
    p->start("cmd.exe", abc);

    /*
    while(p.isOpen()) {

    }
    */
}

void Batch::sh3DC_NewCareer(QString type, QString career, QString newCareerName){

    QStringList abc;
    abc << "/C" << "start" << "/min" << "" << "SH3_Dynamic_Campaign.exe" << "dc" << type << career << newCareerName << "^&" << "exit";
    QProcess *p = new QProcess;
    p->start("cmd.exe", abc);

    /*
    while(p.isOpen()) {

    }
    */
}

void Batch::sh3DC_SH3Cmdr(QString type, QString career){

    QStringList abc;
    QString skip_SH3Commander = "False";
    abc << "/C" << "start" << "/min" << "" << "SH3_Dynamic_Campaign.exe" << "dcsh3c" << type << career << skip_SH3Commander << "^&" << "exit";
    QProcess *p = new QProcess;
    p->start("cmd.exe", abc);

    /*
    while(p.isOpen()) {

    }
    */
}

void Batch::sh3DC_SH3Cmdr_NewCareer(QString type, QString career, QString newCareerName){

    QStringList abc;
    abc << "/C" << "start" << "/min" << "" << "SH3_Dynamic_Campaign.exe" << "dcsh3c" << type << career << newCareerName << "^&" << "exit";
    QProcess *p = new QProcess;
    p->start("cmd.exe", abc);

    /*
    while(p.isOpen()) {

    }
    */
}

void Batch::sh3() {

    QStringList abc;
    abc << "/C" << "start" << "/min" << "" << "SH3_Dynamic_Campaign.exe" << "standard" << "^&" << "exit";
    QProcess *p = new QProcess;
    p->start("cmd.exe", abc);

}

void Batch::backup() {

    QStringList abc;
    abc << "/C" << "start" << "/min" << "" << "SH3_Dynamic_Campaign.exe" << "backup" << "^&" << "exit";
    QProcess *p = new QProcess;
    p->start("cmd.exe", abc);
}

void Batch::crash() {
    QStringList abc;
    abc << "/C" << "start" << "/min" << "" << "SH3_Dynamic_Campaign.exe" << "crash" << "^&" << "exit";
    QProcess *p = new QProcess;
    p->start("cmd.exe", abc);
}

void Batch::uninstall() {
    QStringList abc;
    abc << "/C" << "start" << "/min" << "" << "SH3_Dynamic_Campaign.exe" << "uninstall" << "^&" << "exit";
    QProcess *p = new QProcess;
    p->start("cmd.exe", abc);
}

void Batch::forgotMark(QString career, QString patrol, QString className, QString date, QString longitude, QString latitude) {   
    QStringList abc;
    abc << "/C" << "start" << "/min" << "" << "SCRIPTS\\FORGOT_script.exe" << career << patrol << className << date << longitude << latitude << "^&" << "exit";
    QProcess *p = new QProcess;
    p->start("cmd.exe", abc);
}


bool Batch::scriptsOnly(QString type){
    QStringList abc;
    if(type=="original"){
        abc << "/C" << "start" << "/min" << "" << "SCRIPTS\\ORIGINAL_script.exe" << "^&" << "exit";
        proc = new QProcess;
        proc->start("cmd.exe", abc);
        proc->setObjectName("pScriptsOnly");
        if(proc->state()==QProcess::NotRunning){
            return false;
        }else{
            return true;
        }

    } else if(type=="easy"){
        abc << "/C" << "start" << "/min" << "" << "SCRIPTS\\EASY_script.exe" << "^&" << "exit";
        proc = new QProcess;
        proc->start("cmd.exe", abc);
        proc->setObjectName("pScriptsOnly");
        //p->setProgram("EASY_script.exe");
        //p->waitForStarted(1000);


        if(proc->state()==QProcess::NotRunning){
            return false;
        }else{
            return true;
        }

    }

    return false;

}
/*
void Batch::cancelScript(){
    proc->close();
}
*/

QProcess* Batch::return_Process(){

    return proc;
}
