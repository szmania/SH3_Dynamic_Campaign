//Grabs data/filepaths from DATA/settings.cfg file

#include "mainwindow.h"
#include "grabdata.h"


#include <QDebug>
#include <QObject>
#include <QNetworkAccessManager>
#include <QBuffer>
#include <QFileInfo>
#include <QSettings>
#include <QDirIterator>
#include <QFileDialog>

GrabData::GrabData(QObject *parent) :
    QObject(parent)

{
    nam = new QNetworkAccessManager;
    nam->setObjectName("nam");
    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
    sh3Directory = this->return_sh3Directory();
}

GrabData::~GrabData(){

}


QString GrabData::return_sh3Directory() {
    QString sh3Directory;
    QFile file("DATA/settings.cfg");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.fileName() << file.errorString();
    } else{
        QTextStream in(&file);
        QString line;
        while(!in.atEnd()) {
            line = in.readLine();
            if(line.left(13)=="sh3Directory=") {
                sh3Directory = line.mid(13);
            }
        }
    }
    file.close();
    return sh3Directory;

}

QString GrabData::return_sh3Saves() {

    QString sh3Saves;
    QFile file("DATA/settings.cfg");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.fileName() << file.errorString();
    } else {

        QTextStream in(&file);
        QString line;
        while(!in.atEnd()) {
            line = in.readLine();
            if(line.left(9)=="sh3Saves=") {
                sh3Saves = line.mid(9);
            }
        }
    }
    file.close();
    return sh3Saves;

}

QString GrabData::return_sh3Commander() {
    QString sh3Commander;
    QFile file("DATA/settings.cfg");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.fileName() << file.errorString();
    } else{
        QTextStream in(&file);
        QString line;
        while(!in.atEnd()) {
            line = in.readLine();
            if(line.left(13)=="sh3Commander=") {
                sh3Commander = line.mid(13);
            }
        }
    }
    file.close();
    return sh3Commander;

}

QString GrabData::return_submarineTrackingRoom() {
    QString submarineTrackingRoom;
    QFile file("DATA/settings.cfg");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.fileName() << file.errorString();
    } else{
        QTextStream in(&file);
        QString line;
        while(!in.atEnd()) {
            line = in.readLine();
            if(line.left(22)=="submarineTrackingRoom=") {
                submarineTrackingRoom = line.mid(22);
            }
        }
    }
    file.close();
    return submarineTrackingRoom;

}



void GrabData::export_sh3Directory(QString sh3Directory) {
    adjust_settings_value("DATA/settings.cfg","sh3Directory",sh3Directory);
}

void GrabData::export_sh3Saves(QString sh3Saves) {
    adjust_settings_value("DATA/settings.cfg","sh3Saves",sh3Saves);
}

void GrabData::export_sh3Commander(QString sh3Commander) {
    adjust_settings_value("DATA/settings.cfg","sh3Commander",sh3Commander);
}

void GrabData::export_submarineTrackingRoom(QString submarineTrackingRoom) {
    if (adjust_settings_value("DATA/settings.cfg","submarineTrackingRoom",submarineTrackingRoom) == false) {
        QString line = "submarineTrackingRoom=" + submarineTrackingRoom;
        add_line("DATA/settings.cfg","sh3Commander=", line);
    }
}

bool GrabData::adjust_settings_value(QString filename, QString prefix, QString postfix){

    bool success = false;
    QFile inFile(filename);
    inFile.copy(inFile.fileName()+".bak");
    QFile outFile(inFile.fileName());
    inFile.setFileName(inFile.fileName() + ".bak");

    QString replaceWith = prefix + "=" + postfix;
    //qDebug() << filename << prefix << postfix;

    if ( inFile.open(QIODevice::ReadWrite | QIODevice::Text) && outFile.open(QIODevice::ReadWrite | QIODevice::Text) )
    {
        QTextStream in(&inFile);
        QTextStream out(&outFile);
        QString line;

        while (!in.atEnd())
        {
            line = in.readLine();
            if ((line.startsWith(prefix + "=")))
            {
                QString outline = line.replace(line,replaceWith);
                out << outline << endl;
                success = true;

            }
            else {
                out << line << endl;
            }
        }

    }
    inFile.close();
    inFile.remove();
    outFile.close();
    return success;

}

bool GrabData::replace_line(QString filename, QString prefix, QString replaceWith) {

    bool success = false;
    QFile inFile(filename);
    inFile.copy(inFile.fileName()+".bak");
    QFile outFile(inFile.fileName());
    inFile.setFileName(inFile.fileName() + ".bak");

    //QString replaceWith = prefix + "=" + postfix;
    //qDebug() << filename << prefix << postfix;

    if ( inFile.open(QIODevice::ReadWrite | QIODevice::Text) && outFile.open(QIODevice::ReadWrite | QIODevice::Text) )
    {
        QTextStream in(&inFile);
        QTextStream out(&outFile);
        QString line;

        while (!in.atEnd())
        {
            line = in.readLine();
            if (line.startsWith(prefix))
            {
                QString outline = line.replace(line,replaceWith);
                out << outline << endl;
                success = true;

            }
            else {
                out << line << endl;
            }
        }

    }
    inFile.close();
    inFile.remove();
    outFile.close();
    return success;
}

void GrabData::add_line(QString filename, QString previousLine_Prefix, QString newLine){
    QFile inFile(filename);
    inFile.copy(inFile.fileName()+".bak");
    QFile outFile(inFile.fileName());
    QFile allInFile(inFile.fileName() + ".bak");
    inFile.setFileName(inFile.fileName() + ".bak");

    if ( inFile.open(QIODevice::ReadWrite | QIODevice::Text) && allInFile.open(QIODevice::ReadWrite | QIODevice::Text) && outFile.open(QIODevice::ReadWrite | QIODevice::Text) )
    {        
        QTextStream in(&inFile);
        QTextStream out(&outFile);
        QTextStream allIn(&allInFile);

        if (!(allIn.readAll().contains(newLine, Qt::CaseSensitive))) {

            QString line;

            while (!in.atEnd())
            {
                line = in.readLine();

                if (line.startsWith(previousLine_Prefix))
                {
                    out << line << endl;
                    out << newLine << endl;
                }
                else {
                    out << line << endl;
                }
            }
        }

    }
    allInFile.close();
    inFile.close();
    inFile.remove();
    outFile.close();

}

QString GrabData::return_line(QString prefix){
    QFile file("DATA/settings.cfg");
    if(!file.open(QIODevice::ReadOnly) && file.exists()) {
        qDebug() << file.fileName() << file.errorString();
    } else{

        QTextStream in(&file);
        QString line;
        QString postfix;
        while(!in.atEnd()) {
            line = in.readLine();
            if(line.startsWith(prefix,Qt::CaseSensitive)) {
                postfix = line.mid(prefix.length());
                break;
            }
        }
        file.close();
        return postfix;
    }
    return 0;

}

void GrabData::remove_line(QString prefix) {

    QFile outFile("DATA\\settings.cfg");
    QFile inFile(outFile.fileName()+".bak");

    if(inFile.exists()){
        inFile.remove();
    }
    outFile.copy(inFile.fileName());

    if ( inFile.open(QIODevice::ReadWrite | QIODevice::Text) && outFile.open(QIODevice::ReadWrite | QIODevice::Text) )
    {
        QTextStream in(&inFile);
        QTextStream out(&outFile);
        QString line;

        while (!in.atEnd())
        {
            line = in.readLine();

            if (line.startsWith(prefix + "="))
            {

            }
            else {
                out << line << endl;
            }
        }
    }
    inFile.close();
    inFile.remove();
    outFile.close();
}

void GrabData::convert_settings_to_cfg() {
    QFile settingsFile("DATA\\settings.txt");
    QFileInfo fileInfo(settingsFile);
    if(!QFile::exists(fileInfo.absolutePath()+"/"+fileInfo.baseName()+".cfg")) {
        settingsFile.copy(fileInfo.absolutePath()+"/"+fileInfo.baseName()+".cfg");
    }
    settingsFile.close();
    settingsFile.remove();
}


void GrabData::check_if_settings_file_exists() {

    QFile outFile("DATA\\settings.cfg");
    QFile inFile(outFile.fileName()+".bak");

    if(inFile.exists()){
        inFile.remove();
    }
    outFile.copy(inFile.fileName());

    if(inFile.exists()){
        if ( inFile.open(QIODevice::ReadWrite | QIODevice::Text) && outFile.open(QIODevice::ReadWrite | QIODevice::Text) )
        {
            QTextStream in(&inFile);
            QTextStream out(&outFile);
            QString line;

            while(!in.atEnd()) {
                line = in.readLine();
                out.readLine();

                if(line=="[PREFERENCES]") {
                    break;
                }
            }

            if(in.atEnd()) {
                if (!(line=="")) {
                    out << endl;
                }
                out << "[PREFERENCES]" << endl;
                out << "radSH3DCEasy=" << endl;
                out << "radSH3DCOriginal=" << endl;
                out << "radSH3DCEasy_NC=" << endl;
                out << "radSH3DCOriginal_NC=" << endl;
                out << endl;
                out << "[SETTINGS]" << endl;
                out << "chBoxSh3Commander=" << endl;
                out << "chBoxSubmarineTrackingRoom=" << endl;

            }
        }
    }
    inFile.close();
    inFile.remove();
    outFile.close();

}



void GrabData::imageFromUrlLabel(QLabel *label, QString imagePath){

    lblImageUrl = label;

    QUrl url(imagePath);
    nam->get(QNetworkRequest(url));


}

void GrabData::finishedSlot(QNetworkReply *reply)
{
    // Reading attributes of the reply
    // e.g. the HTTP status code
    QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    // Or the target URL if it was a redirect:
    QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    // no error received?
    if (reply->error() == QNetworkReply::NoError)
    {
        // read data from QNetworkReply here
        QByteArray bytes = reply->readAll();  // bytes
        QPixmap pixmap;

        //QBuffer buffer(&bytes);
        //pixmap.save(&buffer, "GIF");

        QString url = QString("<img src=\"data:image/gif;base64,") + bytes.toBase64() + "\"/>";
        lblImageUrl->setText(url);

        //pixmap.loadFromData(bytes);
        //lblImageUrl->setPixmap(pixmap);

    }
    // Some http error received
    else
    {
        // handle errors here
    }

    // We receive ownership of the reply object
    // and therefore need to handle deletion.
    delete reply;
}


QNetworkAccessManager* GrabData::return_nam()
{
    return nam;
}

void GrabData::adjust_settings_file_for_updates()
{
    check_if_settings_file_exists();
    //upgrade from v1.2b to v1.3 adjustments
    convert_settings_to_cfg();
    remove_line("SH3CmdrCheckBox");
    remove_line("chkSH3Cmdr_NC");
    add_line("DATA/settings.cfg","[SETTINGS]","chBoxSh3Commander=");
    add_line("DATA/settings.cfg","chBoxSh3Commander=","chBoxSubmarineTrackingRoom=");
}



QStringList GrabData::getAllFilesInDir(QString dirPath)
{
    QStringList fileList;
    QDirIterator it(dirPath, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        fileList.append(it.next());

    return fileList;
}



