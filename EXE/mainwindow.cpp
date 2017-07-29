//MainWindow class for main program window

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "batch.h"
#include "populate.h"
#include "table.h"
#include "grabdata.h"
#include "aboutdialog.h"
#include "forgotdialog.h"
#include "backupdialog.h"
#include "crashdialog.h"
#include "externalprograms.h"
#include "sh3dc_startup.h"
#include "memory.h"
#include "sh3monitorthread.h"

#include <QLabel>
#include <QDebug>
#include <QFile>
#include <QList>
#include <Qdir>
#include <QCheckBox>
#include <QLineEdit>
#include <QPainter>
#include <QMessageBox>
#include <QFileSystemWatcher>
#include <QDesktopWidget>
#include <QTranslator>
#include <math.h>
#include <QFileDialog>
#include <QSettings>
//#include <cstdint>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    
    Campaign *campaignObj = new Campaign();
    campaignObj;
//    campaignObj->openCampaignSCR();

    //QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    //QPoint center = desktopRect.center();
    //this->move(center.x()-width()*0.5, center.y()-height()*0.5);

    qDebug() << "Current working directory: " << QDir::currentPath();
//    Memory *MemObj = new Memory();
//    qDebug() << MemObj->readMem_double(0x32671B70);

//    MemObj->readMem_double("30C10250");
//    int value = *reinterpret_cast<int *>(p);

    this->setWindowTitle(tr("SH3 Dynamic Campaign v1.3"));
    //this->setWindowFlags(Qt::Tool);
    this->move(0,0);

    starting_functions();




    /*
     * SH3 Dynamic Campaign.bat commands
     *
        if "%1"=="startup" goto startup
        if "%1"=="dc" goto dynamiccampaign
        if "%1"=="dcsh3c" goto dynamiccampaignsh3commander
        if "%1"=="standard" goto standard
        if "%1"=="backup" goto backup
        if "%1"=="crash" goto crash
        if "%1"=="uninstall" goto uninstall

     * */


}


MainWindow::~MainWindow()
{
    delete ui;
    //delete watcher;
}




void MainWindow::starting_functions(){

//    this->createLogger();
    GrabData *grabData = new GrabData();
    signal_slot_connections();

    grabData->adjust_settings_file_for_updates();

    create_statusBar();
    
    start_sh3MonitoringThread();

    QMap<QString, int> careerDirMap = startup();

    sh3dc_page(careerDirMap);
    

}

void MainWindow::start_sh3MonitoringThread(){
    sh3MonitorThread *sh3MonitorThreadObj =  new sh3MonitorThread();
    sh3MonitorThreadObj->start();

}

//QLoggingCategory MainWindow::createLogger(){
//    QFile *file = new QFile("SH3DC.log");
//    file->open(QIODevice::ReadOnly);
//    *sh3dcLogger = new QTextStream(file);
//}




QMap<QString, int> MainWindow::startup() {
    qDebug() << "Running startup.";
    ui->lblLabel->setParent(this);
    ui->lblLabel->setWordWrap(true);
    ui->lblLabel->setVisible(false);
    ui->pushButton_Next->setVisible(false);

    check_settings_file();
    testSH3Version();

    sh3dc_startup *sh3dc_startupObj = new sh3dc_startup();
    QMap<QString, int> careerDirMap = sh3dc_startupObj->create_CareerDirs();

    return careerDirMap;

//    Batch *batchObj;
//    batchObj = new Batch();
//    batchObj->startup();

}

void MainWindow::sh3dc_page(QMap<QString, int> careerDirMap){

    Populate *populate;
    populate = new Populate();

    ui->careersTW->clear();

    ui->gridLayout->addWidget(ui->pushButton_Next, 20, 1, 1, 1, Qt::AlignRight);


//    QFile file("TEMP\\careers_patrols.tmp");

//    if (!file.open(QIODevice::ReadOnly)) {
      if (careerDirMap.count() == 0){
//        QMessageBox::warning(this, "NO PREVIOUS PATROLS!","Cannot find previous patrols.\nCannot find file: '" + file.fileName().replace("/","\\") + "'");
//        qDebug() << file.fileName() << file.errorString();
        tab = new QWidget(ui->careersTW);
        populate->newCareerTab(tab);
        ui->careersTW->addTab(tab, "New Career");
        connect(populate->return_txtNewCareer(ui->careersTW->currentWidget()), SIGNAL(textEdited(QString)), this, SLOT(txtNewCareer_edited(QString)));

    }
    else {


        for(int i = 0; i < careerDirMap.values().size(); ++i){
            qDebug() << careerDirMap.keys().at(i)  + "-" + QString::number(careerDirMap.values().at(i));
            QString line = careerDirMap.keys().at(i) + "-" + QString::number(careerDirMap.values().at(i));
//        QTextStream in(&file);
//        QString line;
//        int lines = 0;

//        while(!in.atEnd()) {
//            lines++;

//            line = in.readLine();
//            //qDebug() << "line: " << line;

            tab = new QWidget(ui->careersTW);
            populate->careerTab(tab, line);
            QRegExp rx("\\-"); //RegEx for '-'

            QStringList query = line.split(rx);

            ui->careersTW->addTab(tab, query.value(0));

            tab_signal_slot_connects(tab);


        }
    }
//    file.close();

}

void MainWindow::tab_signal_slot_connects(QWidget *tab) {
    Populate *populate;
    populate = new Populate();

    connect(populate->return_btnCareer(tab), SIGNAL(clicked()), this, SLOT(btnCareer_clicked()));

    connect(populate->return_btnScriptsOnly(tab), SIGNAL(clicked()), this, SLOT(btnScriptsOnly_clicked()));

    connect(populate->return_btnRefresh(tab), SIGNAL(clicked()), this, SLOT(btnRefresh_clicked()));

    connect(populate->return_NewCareerCheckBox(tab), SIGNAL(clicked()), this, SLOT(NewCareerCheckBox_clicked()));

    connect(populate->return_radSH3DCEasy(tab), SIGNAL(clicked()), this, SLOT(radioButton_radSH3DCEasy_clicked()));

    connect(populate->return_radSH3DCOriginal(tab), SIGNAL(clicked()), this, SLOT(radioButton_radSH3DCOriginal_clicked()));

    connect(populate->return_btnShowMarksFile(tab), SIGNAL(clicked()), this, SLOT(btnShowMarksFile_clicked()));

    connect(populate->return_lblForgotMark(tab), SIGNAL(linkActivated(const QString &)), this, SLOT(lblForgotMark_clicked(const QString &)));

}

void MainWindow::on_pushButton_Next_clicked()
{  
//    /*

//    Batch *batchObj = new Batch();
//    Populate *populate = new Populate();

//    //if(ui->radioButton_SH3DC->isChecked()){
//        QString type;

//        if (populate->return_radSH3DCEasy_NC(ui->careersTW->currentWidget())->isChecked()) {
//            type = "easy";
//        }
//        else if (populate->return_radSH3DCOriginal_NC(ui->careersTW->currentWidget())->isChecked()) {
//            type = "original";
//        }

//        if (!(populate->return_chkSH3Cmdr_NC(ui->careersTW->currentWidget())->isChecked())) {
//            externalProgramsObj->launch_SH3TrackingRoom();

//            batchObj->sh3DC_NewCareer(type, "newcareer",(populate->return_txtNewCareer(ui->careersTW->currentWidget()))->text());
//        }
//        else if(populate->return_SH3CmdrCheckBox(ui->careersTW->currentWidget())->isChecked()) {
//            externalProgramsObj->launch_SH3TrackingRoom();
//            qDebug() << "bitch";
//            batchObj->sh3DC_SH3Cmdr_NewCareer(type, "newcareer", (populate->return_txtNewCareer(ui->careersTW->currentWidget()))->text());
//        }

//    }
//    else if(ui->radioButton_SH3->isChecked()) {
//        batchObj->sh3();
//    }
//    else if(ui->radioButton_Backup->isChecked()) {
//        batchObj->backup();
//    }
//    else if(ui->radioButton_Crash->isChecked()) {
//        batchObj->crash();
//    }
//    else if(ui->radioButton_Uninstall->isChecked()) {
//        ui->buttonWidget->hide();
//        batchObj->uninstall();

//        this->close();
//    }

//    */
}


/*
void MainWindow::on_radioButton_SH3DC_clicked()
{
    sh3dc_page();
    ui->careersTW->setVisible(true);
    ui->pushButton_Next->setVisible(false);
    ui->lblLabel->setVisible(false);
}

*/

void MainWindow::btnCareer_clicked(){
    Batch *batchObj = new Batch();
    Populate *populate = new Populate();
    GrabData *grabDataObj = new GrabData();

    ExternalPrograms *externalProgramsObj = new ExternalPrograms();


    QString careerName = ui->careersTW->tabText(ui->careersTW->indexOf(ui->careersTW->currentWidget()));
    QString type;

    if (populate->return_radSH3DCEasy(ui->careersTW->currentWidget())->isChecked()) {
        type = "easy";
    }
    else if (populate->return_radSH3DCOriginal(ui->careersTW->currentWidget())->isChecked()) {
        type = "original";
    }

    if ((populate->return_NewCareerCheckBox(ui->careersTW->currentWidget())->isChecked()) && (grabDataObj->return_sh3Commander()=="")) {
        careerName = "newcareer";
        batchObj->sh3DC_NewCareer(type, careerName,(populate->return_NewCareerLineEdit(ui->careersTW->currentWidget()))->text());
    }
    else if((grabDataObj->return_sh3Commander()!="") && !(populate->return_NewCareerCheckBox(ui->careersTW->currentWidget())->isChecked())) {
        externalProgramsObj->launch_submarineTrackingRoom();
        //QProcess *p = externalProgramsObj->return_QProcess();
        //qDebug() << "exit code: " << p->state();
        //connect(p, SIGNAL(finished(int, QProcess::ExitStatus)), externalProgramsObj, SLOT(externalProcessFinished_externalProgramsObj(int, QProcess::ExitStatus)));

        //batchObj->sh3DC_SH3Cmdr(type, careerName);
    }
    else if((grabDataObj->return_sh3Commander()!="") && (populate->return_NewCareerCheckBox(ui->careersTW->currentWidget())->isChecked())) {
        externalProgramsObj->launch_submarineTrackingRoom();

        careerName = "newcareer";
        batchObj->sh3DC_SH3Cmdr_NewCareer(type, careerName, (populate->return_NewCareerLineEdit(ui->careersTW->currentWidget()))->text());
    }
    else{
        batchObj->sh3DC(type, careerName);
    }

}

void MainWindow::btnScriptsOnly_clicked(){
    Batch *batchObj;
    batchObj = new Batch();
    Populate *populate;
    populate = new Populate();

    QString type;

    //if(populate->return_btnScriptsOnly(ui->careersTW->currentWidget())->text()=="Cancel Script") {
    //    batchObj->cancelScript();
    //} else{
        if (populate->return_radSH3DCEasy(ui->careersTW->currentWidget())->isChecked()) {
            type = "easy";
        }
        else if (populate->return_radSH3DCOriginal(ui->careersTW->currentWidget())->isChecked()) {
            type = "original";
        }
        if(batchObj->scriptsOnly(type)){
            //populate->return_btnScriptsOnly(ui->careersTW->currentWidget())->setText("Cancel Script");
            //connect(batchObj->return_Process(), SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(batchProcess_finished(int, QProcess::ExitStatus)));
        }

   // }

}

void MainWindow::btnRefresh_clicked(){

    int index = ui->careersTW->currentIndex();
    int indexPat = ui->careersTW->currentWidget()->findChild<QTabWidget *>("CareersTW_Patrols")->currentIndex();
    QMap<QString, int> careerDirMap = startup();
    sh3dc_page(careerDirMap);
    ui->careersTW->setCurrentWidget(ui->careersTW->widget(index));
    ui->careersTW->currentWidget()->findChild<QTabWidget *>("CareersTW_Patrols")->setCurrentIndex(indexPat);
}

void MainWindow::NewCareerCheckBox_clicked() {
    Populate *populate = new Populate();
    QCheckBox *NewCareerCheckBox = qobject_cast<QCheckBox*>(QObject::sender());

    if((NewCareerCheckBox->checkState())== Qt::Checked) {
        populate->return_NewCareerLineEdit(ui->careersTW->currentWidget())->setDisabled(false);
        populate->return_lblNewCareer(ui->careersTW->currentWidget())->setDisabled(false);

    }
    if((NewCareerCheckBox->checkState())== Qt::Unchecked) {
        populate->return_NewCareerLineEdit(ui->careersTW->currentWidget())->setDisabled(true);
        populate->return_lblNewCareer(ui->careersTW->currentWidget())->setDisabled(true);

    }
}


void MainWindow::radioButton_radSH3DCEasy_clicked() {
    Populate *populate = new Populate();
    populate->return_btnShowMarksFile(ui->careersTW->currentWidget())->setDisabled(true);
    populate->return_lblMarksExample(ui->careersTW->currentWidget())->setDisabled(true);
    populate->return_btnShowMarksFile(ui->careersTW->currentWidget())->setVisible(false);
    populate->return_lblMarksExample(ui->careersTW->currentWidget())->setVisible(false);
}

void MainWindow::radioButton_radSH3DCOriginal_clicked() {

    Populate *populate = new Populate();
    populate->return_btnShowMarksFile(ui->careersTW->currentWidget())->setDisabled(false);
    populate->return_lblMarksExample(ui->careersTW->currentWidget())->setDisabled(false);
    populate->return_btnShowMarksFile(ui->careersTW->currentWidget())->setVisible(true);
    populate->return_lblMarksExample(ui->careersTW->currentWidget())->setVisible(true);

}

void MainWindow::btnShowMarksFile_clicked() {
    QProcess p;
    QStringList abc;
    abc << "/C" << "start" << "notepad" << "Marks.txt";
    p.startDetached("cmd.exe", abc);
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog *aboutObj = new AboutDialog;
    aboutObj->exec();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}


void MainWindow::lblForgotMark_clicked(const QString &link) {
    Populate *populate = new Populate();
    if(link=="forgot") {
        ForgotDialog *forgotObj = new ForgotDialog;
        QRegExp rx("\\ "); //RegEx for ' '
        QStringList query = (populate->returnTW_CareersTW_Patrols(ui->careersTW->currentWidget())->tabText(populate->returnTW_CareersTW_Patrols(ui->careersTW->currentWidget())->indexOf(populate->returnTW_CareersTW_Patrols(ui->careersTW->currentWidget())->currentWidget()))).split(rx);
        forgotObj->populateEntries(ui->careersTW->tabText(ui->careersTW->indexOf(ui->careersTW->currentWidget())), query.value(1));
        forgotObj->exec();
    }
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog *settingsObj = new SettingsDialog;
    settingsObj->exec();
}

void MainWindow::txtNewCareer_edited(QString) {
    Populate *populate = new Populate();
    if (!((populate->return_txtNewCareer(ui->careersTW->currentWidget())->text()).isEmpty())) {
        ui->pushButton_Next->setText("Start New Career");
        ui->pushButton_Next->adjustSize();
        ui->pushButton_Next->setVisible(true);
    } else {
        ui->pushButton_Next->setText("Next");
        ui->pushButton_Next->adjustSize();
        ui->pushButton_Next->setVisible(false);
    }
}
/*
void MainWindow::on_radioButton_SH3DC_toggled(bool checked)
{


    if(checked==false){
        edit_preferences_file("DATA\\settings.cfg");
    }

}
*/

void MainWindow::edit_preferences_file(QString file) {
    Populate *populate = new Populate();
    GrabData *grabData = new GrabData();

    grabData->adjust_settings_value(file, "sh3Directory", grabData->return_sh3Directory());
    grabData->adjust_settings_value(file, "sh3Saves", grabData->return_sh3Saves());
    grabData->adjust_settings_value(file, "sh3Commander", grabData->return_sh3Commander());

//    QFile patFile("TEMP\\careers_patrols.tmp");


//    if (patFile.open(QIODevice::ReadOnly)) {
       grabData->adjust_settings_value(file, "radSH3DCEasy", QString::number(populate->return_radSH3DCEasy(ui->careersTW->currentWidget())->isChecked()));
       grabData->adjust_settings_value(file, "radSH3DCOriginal", QString::number(populate->return_radSH3DCOriginal(ui->careersTW->currentWidget())->isChecked()));
//       patFile.close();
//    } else {
       grabData->adjust_settings_value(file, "radSH3DCEasy_NC", QString::number(populate->return_radSH3DCEasy_NC(ui->careersTW->currentWidget())->isChecked()));
       grabData->adjust_settings_value(file, "radSH3DCOriginal_NC", QString::number(populate->return_radSH3DCOriginal_NC(ui->careersTW->currentWidget())->isChecked()));
//    }


}

void MainWindow::closeEvent(QCloseEvent*)
{
    edit_preferences_file("DATA\\settings.cfg");
}

void MainWindow::scriptStatusFileChanged(const QString& filePath){


    //QFile file("TEMP/script_status.log");
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.fileName() << file.errorString();
    } else {

        QTextStream in(&file);
        QString line;


        while(!in.atEnd()) {
            line = in.readLine();


            //ui->statusBar->showMessage(line);


            //ui->statusBar->findChild<QLabel *>("postfix")->setText(line);
            //postfix2->setText(line);
            //postfix->setText(line);
        }
        ui->statusBar->showMessage(line);

    }
    file.close();

}


void MainWindow::signal_slot_connections(){


    BackupDialog *backupObj = new BackupDialog();
    CrashDialog *crashObj = new CrashDialog();
    UninstallDialog *uninstallObj = new UninstallDialog();
    QFileSystemWatcher *watcher = new QFileSystemWatcher;
//    GrabData *grabDataObj = new GrabData();


    watcher->addPath("TEMP\\script_status.log");


    connect(watcher, SIGNAL(fileChanged(const QString&)), this, SLOT(scriptStatusFileChanged(const QString&)));

    connect(watcher, SIGNAL(fileChanged(const QString&)), backupObj, SLOT(scriptStatusFileChanged_backupObj(const QString&)));

    connect(watcher, SIGNAL(fileChanged(const QString&)), crashObj, SLOT(scriptStatusFileChanged_crashObj(const QString&)));

    connect(watcher, SIGNAL(fileChanged(const QString&)), uninstallObj, SLOT(scriptStatusFileChanged_uninstallObj(const QString&)));

//    connect(grabDataObj, SIGNAL(show_findDir()), this, SLOT(get_directory_dialog()));

    //grabData->imageFromUrlLabel(ui->label, "http://www.uboat.net/media/boats/emblems/u2.gif");


}

void MainWindow::testSH3Version(){
    GrabData *grabData = new GrabData();

    QFile file(grabData->return_sh3Directory()+"/data/Menu/en_menu.txt");


    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.fileName() << file.errorString();
    } else{

        QTextStream in(&file);
        QString line;
        bool found=false;

        while(!in.atEnd()) {
            line = in.readLine();
            if(line=="2254=Mark %d"){
                found=true;
            }
        }

        if(!found){
            QMessageBox::warning(this, "Update Silent Hunter III to version 1.4b!","<qt>In order for SH3 Dynamic Campaign to \noperate correctly Silent Hunter III needs \nto be updated to version 1.4b. <br/><br/><b> Download <a href=\"http://www.silenthunteriii.com/uk/updates.php\">HERE</a></b></qt>" );
            this->close();
        }
    }
}

void MainWindow::create_statusBar(){
    QLabel *postfix = new QLabel(this);
    postfix->setText("Script Status");
    postfix->setStyleSheet("QLabel { color: red; font: bold;}");
    ui->statusBar->addPermanentWidget(postfix);

    //QLabel *postfix = new QLabel(this);
    //ui->statusBar->insertWidget(postfix);
}

/*
void MainWindow::batchProcess_finished(int, QProcess::ExitStatus){

    Populate *populate = new Populate();
    populate->return_btnScriptsOnly(ui->careersTW->currentWidget())->setText("Run Script Only");
}
*/





void MainWindow::on_actionBackup_Files_triggered()
{
    BackupDialog *backupObj = new BackupDialog;
    backupObj->exec();
}

void MainWindow::on_actionCrash_Recovery_triggered()
{
    CrashDialog *crashObj = new CrashDialog;
    crashObj->exec();
}

void MainWindow::on_actionUninstall_SH3DC_triggered()
{
    UninstallDialog *uninstallObj = new UninstallDialog;
    uninstallObj->exec();
}

void MainWindow::check_settings_file()
{
    GrabData *grabData = new GrabData();

    if (grabData->return_sh3Directory() == ""){
        QSettings registry("HKEY_LOCAL_MACHINE\\SOFTWARE\\Ubisoft\\Silent Hunter III",QSettings::NativeFormat);

        if (registry.contains("InstalledPath") == true) {
            QVariant regValue = registry.value("InstalledPath");
            QString regStr = regValue.toString();
            regStr = regStr.left(regStr.length()-1);
            grabData->export_sh3Directory(regStr);
        }else {
            QString programFilesPath(getenv("PROGRAMFILES"));
            QString directory = this->get_directory_dialog("Find Silent Hunter III directory", programFilesPath+"\\Ubisoft\\SilentHunterIII");
            if (directory != NULL) {
                grabData->export_sh3Directory(directory);
            }
        }
    }
    if (grabData->return_sh3Saves() == ""){

        QString savesPath(getenv("USERPROFILE"));
        QDir savesDir = savesPath+"\\Documents\\SH3";
        if (!savesDir.exists()) {
            QString directory = this->get_directory_dialog("Find Silent Hunter III saves directory", savesPath+"\\Documents\\SH3");
            if (directory != NULL) {
                grabData->export_sh3Saves(directory);

            }
        } else{
            grabData->export_sh3Saves(savesPath+"\\Documents\\SH3");

        }
    }






}

QString MainWindow::get_directory_dialog(QString windowTitle, QString rootPath){
    QFileDialog dialog;
    QString executable = dialog.getExistingDirectory(this, windowTitle, rootPath, QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(executable != NULL) {
        return executable.replace("/","\\");
    }
    else{
        return NULL;
    }

}


