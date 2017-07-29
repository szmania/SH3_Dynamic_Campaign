#ifndef BATCH_H
#define BATCH_H


#include <qdebug.h>

#include <QProcess>
#include <QString>


class Batch
{
public:
    Batch();
    ~Batch();
    void startup();
    void sh3DC(QString, QString);
    void sh3DC_NewCareer(QString, QString, QString);
    void sh3DC_SH3Cmdr(QString, QString);
    void sh3DC_SH3Cmdr_NewCareer(QString, QString, QString);
    void sh3();
    void backup();
    void crash();
    void uninstall();
    void forgotMark(QString, QString, QString, QString, QString, QString);
    bool scriptsOnly(QString);
    void submarineTrackingRoom_monitor();
    //void cancelScript();

    QProcess* return_Process();

private slots:

private:
    QProcess *proc;



};

#endif // BATCH_H
