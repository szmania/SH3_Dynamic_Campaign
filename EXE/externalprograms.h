#ifndef EXTERNALPROGRAMS_H
#define EXTERNALPROGRAMS_H

#include <QObject>

#include "mainwindow.h"

class ExternalPrograms: public QObject
{
    Q_OBJECT
public:
    explicit ExternalPrograms(QObject *parent = 0);
    ~ExternalPrograms();

    void launch_submarineTrackingRoom();
    QProcess* return_QProcess();
private:
    QProcess *process;

private slots:
//    void SH3TrackingRoom_ProcessFinished(int, QProcess::ExitStatus);

};

#endif // EXTERNALPROGRAMS_H
