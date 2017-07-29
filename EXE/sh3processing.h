#ifndef SH3PROCESSING_H
#define SH3PROCESSING_H

#include <QtCore>

class sh3Processing : public QThread
{
public:
    sh3Processing();
    void run();
    QString wait_and_getCareerName();

signals:

public slots:

};

#endif // SH3PROCESSING_H
