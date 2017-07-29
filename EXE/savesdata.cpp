//Grab save data for each game save from the save directory

#include "mainwindow.h"
#include "savesdata.h"

#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QDate>

SavesData::SavesData()
{
}

SavesData::~SavesData(){
}


QString SavesData::find_Data(QString, QString patrolNum, QString filePath, QString find){
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.fileName() << file.errorString();
    } else{

        QTextStream in(&file);
        QString line;
        while(!in.atEnd()) {
                    line = in.readLine();
                    if(!(line.indexOf("PatrolNumber="+patrolNum, 0, Qt::CaseSensitive)==-1)) {
                        while(!in.atEnd()) {
                            line = in.readLine();
                            if(!(line.indexOf(find, 0, Qt::CaseSensitive)==-1)) {
                                QRegExp rx("\\="); //RegEx for '='
                                QStringList query = line.split(rx);
                                file.close();
                                return query.value(1);
                            }
                        }
                    }

        }
    }
    file.close();
    return 0;
}

QString SavesData::career_StartDate(QString career) {
        GrabData *grabDataObj = new GrabData();

    QFile file(grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg");

    if(!file.exists()) {
        file.close();
        qDebug() << file.fileName() << "file does not exist";

        QString year = find_Data(career, "0", grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols_0.cfg", "StartYear");
        QString month = find_Data(career, "0", grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols_0.cfg", "StartMonth");
        QString day = find_Data(career, "0", grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols_0.cfg", "StartDay");

        QDate date(QDate::fromString(year+month+day, "yyyyMd"));
        return date.toString("d MMMM yyyy");
    } else{
        file.close();

        QString year = find_Data(career, "0", grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg", "StartYear");
        QString month = find_Data(career, "0", grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg", "StartMonth");
        QString day = find_Data(career, "0", grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg", "StartDay");

        QDate date(QDate::fromString(year+month+day, "yyyyMd"));

        return date.toString("d MMMM yyyy");
    }
    file.close();
    return 0;

}

QString SavesData::patrol_StartDate(QString career, QString PatrolNum) {
        GrabData *grabDataObj = new GrabData();
    QFile file(grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg");

    if(!file.exists()) {
        file.close();

        QString year = find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols_0.cfg", "StartYear");
        QString month = find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols_0.cfg", "StartMonth");
        QString day = find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols_0.cfg", "StartDay");

        QDate date(QDate::fromString(year+month+day, "yyyyMd"));

        return date.toString("d MMMM yyyy");
    } else {
        file.close();

        QString year = find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg", "StartYear");
        QString month = find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg", "StartMonth");
        QString day = find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg", "StartDay");

        QDate date(QDate::fromString(year+month+day, "yyyyMd"));

        return date.toString("d MMMM yyyy");
    }
    file.close();
    return 0;
}

QString SavesData::patrol_EndDate(QString career, QString PatrolNum) {
        GrabData *grabDataObj = new GrabData();

    QFile file(grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg");

    if(!file.exists()) {
        file.close();

        return "None";
    } else{
        file.close();
        QString year = find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg", "EndYear");
        QString month = find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg", "EndMonth");
        QString day = find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg", "EndDay");

        QDate date(QDate::fromString(year+month+day, "yyyyMd"));

        return date.toString("d MMMM yyyy");
    }
    file.close();
    return 0;

}

QString SavesData::subType(QString career, QString PatrolNum) {
    GrabData *grabDataObj = new GrabData();
    QFile file(grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg");
    QString subClass;
    QString subVersion;

    if(!file.exists()) {

        subClass =  find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols_0.cfg", "SubType");
        subVersion =  find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols_0.cfg", "SubVersion");

    } else{
        subClass =  find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg", "SubType");
        subVersion =  find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg", "SubVersion");

    }
    file.close();

    //qDebug() << "subClass " + subClass;
    //qDebug() << "subVersion " + subVersion;

    QFile file2(grabDataObj->return_sh3Directory() + "/data/Cfg/Basic.cfg");
    file2.setPermissions(QFileDevice::ReadOther);
    if(!file2.open(QIODevice::ReadOnly)) {
        qDebug() << file2.fileName() << file2.errorString();
    } else{

        QTextStream in(&file2);
        QString line;

        while(!in.atEnd()) {
            line = in.readLine();
            //qDebug() << "line " + line;

            if ((line.startsWith("[SUBMARINE"+ subClass + "]"))){
                while(!(line.startsWith("Version"+subVersion+"="+subVersion))){
                    line = in.readLine();
                };

                line = in.readLine();
                //qDebug() << "line " + line;
                QRegExp rx("\\="); //RegEx for '='
                QStringList query = line.split(rx);
                file2.close();
                return query.value(1);

            }
        }
    }
    file2.close();

    return 0;

}

QString SavesData::subName(QString career, QString PatrolNum) {
    GrabData *grabDataObj = new GrabData();
    QFile file(grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg");
    if(!file.exists()) {
        file.close();
        return find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols_0.cfg", "SubName");
    } else{
        file.close();
        return find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg", "SubName");
    }
    file.close();
    return 0;
}

QString SavesData::flotilla(QString career, QString PatrolNum) {
    GrabData *grabDataObj = new GrabData();
    QFile file(grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg");
    if(!file.exists()) {
        file.close();

        QString flotilla = find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols_0.cfg", "Flotilla");
        return find_generalData(grabDataObj->return_sh3Directory() + "/data/Menu/en_menu.txt", flotilla);
    } else{
        file.close();

        QString flotilla = find_Data(career, PatrolNum, grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Patrols.cfg", "Flotilla");
        return find_generalData(grabDataObj->return_sh3Directory() + "/data/Menu/en_menu.txt", flotilla);
    }
    file.close();

    return 0;

}

QString SavesData::find_generalData(QString filePath, QString find){
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.fileName() << file.errorString();
    } else {

        QTextStream in(&file);
        QString line;
        while(!in.atEnd()) {
                            line = in.readLine();
                            if(!(line.indexOf(find, 0, Qt::CaseSensitive)==-1)) {
                                QRegExp rx("\\="); //RegEx for '='
                                QStringList query = line.split(rx);
                                file.close();
                                return query.value(1);
                            }



        }
    }
    file.close();
    return 0;
}


