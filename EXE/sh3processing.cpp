#include "sh3processing.h"
#include "memory.h"
#include "campaign.h"

#include <QtCore>
#include <QDir>

sh3Processing::sh3Processing()
{
}

void sh3Processing::run(){

    Memory *MemoryObj = new Memory();
    while(MemoryObj->sh3IsRunning()){

        QString careerName = wait_and_getCareerName();

        Campaign *CampaignObj = new Campaign();
        CampaignObj->copyCareerFilesToSH3Dir(careerName);

        QThread::sleep(10);
    }


}

QString sh3Processing::wait_and_getCareerName(){
    Memory *MemoryObj = new Memory();
    while(MemoryObj->getCareerName() == ""){
        QThread::sleep(1);
    }
    return MemoryObj->getCareerName();
}
