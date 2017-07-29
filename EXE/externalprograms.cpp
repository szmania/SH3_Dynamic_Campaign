#include "externalprograms.h"
#include "grabdata.h"

#include <QObject>
#include <QMessageBox>

#include <QDir>

ExternalPrograms::ExternalPrograms(QObject *parent):
    QObject(parent)
{

}

ExternalPrograms::~ExternalPrograms()
{
}

void ExternalPrograms::launch_submarineTrackingRoom(){

    GrabData *grabdataObj = new GrabData;
    QString submarineTrackingRoom = grabdataObj->return_submarineTrackingRoom();
    if(submarineTrackingRoom != ""){

        QFile file(submarineTrackingRoom);
        QFileInfo fileInfo(file);

        QFile iniFile(fileInfo.absolutePath() + "/" + fileInfo.baseName() + ".ini");

        QString here = fileInfo.absolutePath() + "/" + fileInfo.baseName() + ".ini";

        if(!iniFile.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(NULL, "Submarine Tracking Room error!","Cannot find \"Submarine Tracking Room\" executable \nCannot find file: '" + file.fileName().replace("/","\\") + "'");

            qDebug() << iniFile.fileName() << iniFile.errorString();
        } else{
            QTextStream in(&iniFile);
            QString line;
            //while(!in.atEnd()) {
            for(int i=0; i < 2; i++){
                line = in.readLine();
            }
            //qDebug() << "line: " << line;
        }
        iniFile.close();

        process = new QProcess();

        QStringList arguments;

        process->setWorkingDirectory(fileInfo.absolutePath());
        process->start(submarineTrackingRoom.replace("\\","/"),arguments);

//        connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(SH3TrackingRoom_ProcessFinished(int, QProcess::ExitStatus)));

    }

}

//void ExternalPrograms::SH3TrackingRoom_ProcessFinished(int exitCode, QProcess::ExitStatus) {

//}


QProcess* ExternalPrograms::return_QProcess(){
    QString prog = process->program();
    return process;
}


