#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include <QObject>
#include <QFile>

class Campaign : public QObject
{
    Q_OBJECT
public:
    explicit Campaign(QObject *parent = 0);
    ~Campaign();
    void openCampaignSCR();
    void copyCareerFilesToSH3Dir(QString);

signals:
private:
    QFile fileCampaignSCR;

public slots:

};

#endif // CAMPAIGN_H
