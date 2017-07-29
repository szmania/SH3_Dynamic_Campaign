#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grabdata.h"
#include "aboutdialog.h"
#include "populate.h"
#include "batch.h"
#include "table.h"
#include "savesdata.h"
#include "forgotdialog.h"
#include "settingsdialog.h"
#include "backupdialog.h"
#include "crashdialog.h"
#include "uninstalldialog.h"
#include "externalprograms.h"
#include "sh3dc_startup.h"
#include "memory.h"
#include "campaign.h"


#include <QMainWindow>
#include <QFileSystemWatcher>
#include <QMessageBox>
#include <QNetworkReply>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class SettingsDialog;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



public slots:
    QString get_directory_dialog(QString, QString);

signals:


protected:


protected slots:


private:
    
    void starting_functions();
    void start_sh3MonitoringThread();
    QMap<QString, int> startup();
    void sh3dc_page(QMap<QString, int>);
    void signal_slot_connections();
    void edit_preferences_file(QString); 
    void closeEvent(QCloseEvent*);

private slots:
    void on_pushButton_Next_clicked();
    void btnRefresh_clicked();
    //void on_radioButton_SH3DC_clicked();
    void btnCareer_clicked();
    void btnScriptsOnly_clicked();
    void NewCareerCheckBox_clicked();
    //void on_radioButton_Uninstall_clicked();
    //void on_radioButton_SH3_clicked();
    //void on_radioButton_Backup_clicked();
    //void on_radioButton_Crash_clicked();
    void radioButton_radSH3DCEasy_clicked();
    void radioButton_radSH3DCOriginal_clicked();
    void btnShowMarksFile_clicked();
    void lblForgotMark_clicked(const QString &link);
    void txtNewCareer_edited(QString text);


    //void on_radioButton_SH3DC_toggled(bool checked);
    void scriptStatusFileChanged(const QString&);
    void testSH3Version();
    void create_statusBar();
    void check_settings_file();
    void tab_signal_slot_connects(QWidget*);

    //void batchProcess_finished(int, QProcess::ExitStatus);


    void on_actionAbout_triggered();
    void on_actionExit_triggered();
    void on_actionSettings_triggered();
    void on_actionBackup_Files_triggered();
    void on_actionCrash_Recovery_triggered();
    void on_actionUninstall_SH3DC_triggered();

private:
    Ui::MainWindow *ui;
    QWidget *tab;




};

#endif // MAINWINDOW_H










