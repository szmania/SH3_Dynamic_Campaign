#ifndef SAVESDATA_H
#define SAVESDATA_H


#include "grabdata.h"

#include <QString>

class SavesData
{
public:
    SavesData();
    ~SavesData();
    QString find_Data(QString, QString, QString, QString);
    QString find_generalData(QString, QString);
    QString career_StartDate(QString);
    QString patrol_StartDate(QString, QString);
    QString patrol_EndDate(QString, QString);
    QString subType(QString, QString);
    QString subName(QString, QString);
    QString flotilla(QString, QString);

private:

};

#endif // SAVESDATA_H
