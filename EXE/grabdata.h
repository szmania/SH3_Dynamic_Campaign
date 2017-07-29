#ifndef GRABDATA_H
#define GRABDATA_H



#include <QWidget>
#include <QFile>
#include <QObject>
#include <QNetworkAccessManager>
#include <QLabel>

class GrabData : public QObject
{
    Q_OBJECT
public:


    explicit GrabData(QObject *parent = 0);
    ~GrabData();

    QString return_sh3Directory();
    QString return_sh3Saves();
    QString return_sh3Commander();
    QString return_submarineTrackingRoom();
    void export_sh3Directory(QString);
    void export_sh3Saves(QString);
    void export_sh3Commander(QString);
    void export_submarineTrackingRoom(QString);
    bool adjust_settings_value(QString,QString,QString);
    bool replace_line(QString,QString,QString);
    void add_line(QString,QString,QString);
    void remove_line(QString);
    void check_if_settings_file_exists();
    //void create_initial_preferences_file();
    QString return_line(QString);
    void imageFromUrlLabel(QLabel*, QString);
    void adjust_settings_file_for_updates();
    void convert_settings_to_cfg();
    bool check_if_dirs_in_settings_exist();
    QStringList getAllFilesInDir(QString);



    QNetworkAccessManager* return_nam();

    QString sh3Directory;


protected:



signals:
    //void messageBox_Signal(QString,QString,QString);
    QString show_findDir();


private slots:
    void finishedSlot(QNetworkReply*);
private:
    QNetworkAccessManager *nam;
    QLabel *lblImageUrl;


};

#endif // GRABDATA_H
