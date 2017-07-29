#include "mainwindow.h"
#include "sh3dc_startup.h"
#include "grabdata.h"

#include <QDir>
#include <QDebug>
#include <QMap>
#include <QRegExp>

sh3dc_startup::sh3dc_startup(QObject *parent) : QObject(parent)
{
    sh3CareerDefaultFiles << "\\data\\Campaigns\\Campaign\\Campaign_SCR.mis"
                             ;

}

sh3dc_startup::~sh3dc_startup(){

}

QMap<QString, int> sh3dc_startup::create_CareerDirs(){
    GrabData *grabData = new GrabData();
    QDir savesCareersDir = grabData->return_sh3Saves() + "\\data\\cfg\\Careers";
    QFileInfoList career_dirList = savesCareersDir.entryInfoList(QDir::NoDotAndDotDot |QDir::Dirs);

    QMap<QString, int> dirMap;
    foreach(QFileInfo career_dirInfo, career_dirList){
        QDir career_dir = career_dirInfo.absoluteFilePath();
        QDir new_careerDir = "Careers\\" + career_dirInfo.fileName();
        copyStockCampaignFiles(career_dir.dirName());

        if (!new_careerDir.exists()){
            new_careerDir.mkpath(".");
        }
        copyStockCampaignFiles(career_dir.dirName());

        QFileInfoList patrol_dirList = career_dir.entryInfoList(QDir::NoDotAndDotDot |QDir::Dirs);
        int patrolCount = 0;
        foreach(QFileInfo patrol_dirInfo, patrol_dirList){
            QRegExp rx("\\d");
            if(!patrol_dirInfo.fileName().contains(QRegExp("a-zA-Z\\s"))) {
                patrolCount++;
            }
        }
        dirMap[career_dirInfo.fileName()] = patrolCount;

    }
    return dirMap;

}


void sh3dc_startup::copyStockCampaignFiles(QString careerName){
    GrabData *grabData = new GrabData();

    QString careerDir_path = QDir::currentPath() + "\\Careers\\" + careerName;

    for (int i=0;i < sh3CareerDefaultFiles.length();i++){
        QString sh3CampaignSCRFile_path = QDir::fromNativeSeparators(grabData->return_sh3Directory() + sh3CareerDefaultFiles[i]);
        QString stockFile = QDir::fromNativeSeparators(careerDir_path + sh3CareerDefaultFiles[i]);
//        QFile stockFileObj(stockFile);
        if (!QFile::exists(stockFile)) {
            qDebug() << sh3CampaignSCRFile_path;
            qDebug() << stockFile;

            QDir().mkpath(QFileInfo(stockFile).absolutePath());
            QFile::copy(sh3CampaignSCRFile_path, stockFile);
        }
    }
}


QMap<QString, int> sh3dc_startup::get_CareerDirs(){
//    GrabData *grabData = new GrabData();
    QDir careersDir = QDir::currentPath() + "\\Careers";
    QFileInfoList career_dirList = careersDir.entryInfoList(QDir::NoDotAndDotDot |QDir::Dirs);

    QMap<QString, int> dirMap;
    foreach(QFileInfo career_dirInfo, career_dirList){
        QDir career_dir = career_dirInfo.absoluteFilePath();
        QFileInfoList patrol_dirList = career_dir.entryInfoList(QDir::NoDotAndDotDot |QDir::Dirs);
        int patrolCount = 0;
        foreach(QFileInfo patrol_dirInfo, patrol_dirList){
            QRegExp rx("\\d");
            if(!patrol_dirInfo.fileName().contains(QRegExp("a-zA-Z\\s"))) {
                patrolCount++;
            }
        }
        dirMap[career_dirInfo.fileName()] = patrolCount;

    }
    return dirMap;

}



