#ifndef SH3DC_STARTUP_H
#define SH3DC_STARTUP_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QStringList>

class sh3dc_startup : public QObject
{
    Q_OBJECT
public:
    explicit sh3dc_startup(QObject *parent = 0);
    ~sh3dc_startup();
    QMap<QString, int> create_CareerDirs();
    QMap<QString, int> get_CareerDirs();
    void copyStockCampaignFiles(QString);

signals:

private:
    QStringList sh3CareerDefaultFiles;

public slots:
};

#endif // SH3DC_STARTUP_H
