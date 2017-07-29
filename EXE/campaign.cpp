#include "campaign.h"
#include "grabdata.h"
#include "memory.h"
#include "sh3dc_startup.h"

#include <QFile>
#include <QDir>

Campaign::Campaign(QObject *parent) :
    QObject(parent)
{

}
Campaign::~Campaign(){

}

void Campaign::openCampaignSCR(){
//    GrabData *grabDataObj = new GrabData();
    Memory *memoryObj = new Memory();
    QString careerName = memoryObj->getCareerName();

    QFile fileCampaignSCR("/Careers/"+ careerName +"/data/Campaigns/campaign/Campaign_SCR.mis");
    if(!fileCampaignSCR.open(QIODevice::ReadOnly)) {
        qDebug() << fileCampaignSCR.fileName() << fileCampaignSCR.errorString();
    } else{
    }
}

void Campaign::copyCareerFilesToSH3Dir(QString careerName){
    qDebug()<<"Copying career campaign files to sh3 directory.";
    QDir careerDir = QDir::currentPath() + "Careers\\" + careerName;
    if (!careerDir.exists()){
        qDebug() << "Career" << careerName << " files do not exist.";
        sh3dc_startup *sh3dc_startupObj = new sh3dc_startup();
        QMap<QString, int> map = sh3dc_startupObj->create_CareerDirs();

    }

    QDir careerFile = QDir::currentPath() + "\\Careers\\" + careerName;
    GrabData *GrabDataObj = new GrabData();
    QStringList careerFiles_list= GrabDataObj->getAllFilesInDir(careerFile.absolutePath());

    for(int i = 0;i < careerFiles_list.length();i++){
        QString path = careerFiles_list[i];
        QRegExp rx("/"); //RegEx for '/'
        QStringList queryList = path.split(rx);
        bool dataFound = false;
        QString relativePath = "";
        for(int j = 0; j < queryList.length();j++){
            if(queryList[j] == "data"){
                dataFound = true;
            }
            if(dataFound == true){
                relativePath = relativePath + "/" + queryList[j];
            }
        }

        qDebug();
        QString copyToPath = GrabDataObj->return_sh3Directory() + "/" + relativePath;
        QFile copyToFile(copyToPath);
        if(copyToFile.exists()){
            QString backupFilePath = QDir::currentPath() + "\\Careers\\_BACKUPS\\" + relativePath;
            QFile backupFile(backupFilePath);
            QFileInfo backupFileInfo(backupFile);
            QDir new_dir(backupFileInfo.absoluteDir());
            new_dir.mkpath(".");
            QFile::copy(copyToPath, backupFilePath);
        }
        QFile::copy(path, copyToPath);

    }


}




