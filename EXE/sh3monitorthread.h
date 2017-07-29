#ifndef SH3MONITORTHREAD_H
#define SH3MONITORTHREAD_H

#include <QtCore>

class sh3MonitorThread : public QThread
{
public:
    sh3MonitorThread();
    void run();
    void monitor();
};

#endif // SH3MONITORTHREAD_H
