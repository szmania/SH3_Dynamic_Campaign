#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QDebug>
#include <QResource>
#include <QTreeView>
#include <QtCore>
#include <QFileDialog>
#include <QDialog>
#include <QSplashScreen>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    this->page = 1;

    QDir sh3DCTemp("SH3 Dynamic Campaign - Full");
    if (sh3DCTemp.exists()) {
        if(!sh3DCTemp.removeRecursively()) {
            qDebug() << "Directory 'SH3 Dynamic Campaign - Full' could not be deleted";
            QMessageBox::warning(this, "DIRECTORY COULD NOT BE REMOVED","Could not delete temporary directory: '" + sh3DCTemp.absolutePath() + "'");

        }
    }

    this->programFilesPath = (qgetenv("PROGRAMFILES"));
    this->SH3ProgramFilesPath = programFilesPath + "\\Ubisoft\\SilentHunterIII";
    this->fullSH3ProgramFilesPath = SH3ProgramFilesPath + "\\sh3.exe";
    this->userProfilePath = (qgetenv("USERPROFILE"));
    this->fullUserProfilePath = userProfilePath + "\\Documents\\SH3";
    this->SH3CommanderPath = programFilesPath + "\\SH3 Commander";
    this->fullSH3CommanderPath = SH3CommanderPath + "\\SH3Cmdr.exe";

    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
                               this, SLOT(updateChecks(QTreeWidgetItem*, int)));



    //Introduction
    ui->label_Title->setText("Introduction");
    //Disclaimer
    ui->textEdit->setVisible(false);
    ui->pushButton_Prev->setVisible(false);
    ui->radioButton_Disagree->setVisible(false);
    ui->radioButton_Agree->setVisible(false);

    //Installation directories
    ui->label_SH3Install->setVisible(false);
    ui->lineEdit_SH3Install->setVisible(false);
    ui->label_SH3Saves->setVisible(false);
    ui->lineEdit_SH3Saves->setVisible(false);
    ui->label_SH3Commander->setVisible(false);
    ui->lineEdit_SH3Commander->setVisible(false);
    ui->checkBox->setVisible(false);
    ui->label_installItems->setVisible(false);
    ui->pushButton_DirSaves->setVisible(false);
    ui->pushButton_DirSH3->setVisible(false);
    ui->pushButton_DirSH3Cmdr->setVisible(false);
    ui->treeWidget->setVisible(false);

    //Installation
    ui->label_ProgressBar->setVisible(false);
    ui->progressBar->setVisible(false);
    ui->progressBar->setValue(0);
    ui->label_ProgressBar->setText("Initializing...");

    //Finish
    ui->checkBox_Shortcut->setChecked(true);
    ui->checkBox_Shortcut->setVisible(false);

    sh3dcFullPack = new QTreeWidgetItem;
    fullPack = new QTreeWidgetItem;
    captainsJournal_FullPack = new QTreeWidgetItem;
    sh3dc = new QTreeWidgetItem;
    captainsJournal = new QTreeWidgetItem;



}

MainWindow::~MainWindow()
{   
    delete ui;
}



void MainWindow::on_pushButton_Next_clicked()
{
    this->page++;
    if(page==4) {
        // Set variables to what is entered in line edits
        this->SH3ProgramFilesPath = ui->lineEdit_SH3Install->text();
        this->userProfilePath = ui->lineEdit_SH3Saves->text();
        this->SH3CommanderPath = ui->lineEdit_SH3Commander->text();
        checkIfExists(&SH3ProgramFilesPath, &userProfilePath, &SH3CommanderPath);
    }

    switch (this->page){
    //Disclaimer
    case 2:
        //set visible elements for Disclaimer
        ui->label_Para->setVisible(false);

        ui->textEdit->setVisible(true);
        ui->pushButton_Prev->setVisible(true);
        ui->radioButton_Disagree->setVisible(true);
        ui->radioButton_Agree->setVisible(true);

        //other
        ui->label_Title->setText("Disclaimer");
        ui->radioButton_Disagree->setChecked(true);
        ui->pushButton_Next->setDisabled(true);
        ui->textEdit->setReadOnly(true);
    break;

    //Installation directories
    case 3:
        unzip();


    break;

    //Installation
    case 4:


        // Disable old widgets
        ui->label_SH3Install->setVisible(false);
        ui->lineEdit_SH3Install->setVisible(false);
        ui->label_SH3Saves->setVisible(false);
        ui->lineEdit_SH3Saves->setVisible(false);
        ui->label_SH3Commander->setVisible(false);
        ui->lineEdit_SH3Commander->setVisible(false);
        ui->checkBox->clicked(false);
        ui->checkBox->setVisible(false);
        ui->treeWidget->setVisible(false);
        ui->label_installItems->setVisible(false);
        ui->pushButton_DirSaves->setVisible(false);
        ui->pushButton_DirSH3->setVisible(false);
        ui->pushButton_DirSH3Cmdr->setVisible(false);

        // Title
        ui->label_Title->setText("Installing");

        // Visible Items
        ui->label_ProgressBar->setVisible(true);
        ui->progressBar->setVisible(true);

        ui->pushButton_Next->setVisible(false);
        ui->pushButton_Prev->setText("Cancel");
        ui->pushButton_Exit->setVisible(false);


        outputPaths(&SH3ProgramFilesPath, &userProfilePath, &SH3CommanderPath);

        if (fullPack->checkState(0)) {
            batPath = "SH3 Dynamic Campaign - Full/SH3DC Full - Installer.bat";

            for (int x=0; x<26 ;x++) {
                ui->progressBar->setValue(x);
            }
            ui->label_ProgressBar->setText("Initializing SH3 Dynamic Campaign - Full Install Package...");
            launchBat(&batPath);

            for (int x=76;x < 101;x++) {
                ui->progressBar->setValue(x);
            }
            ui->label_ProgressBar->setText("Finished!");
        }

        ui->label_ProgressBar->setVisible(false);
        ui->progressBar->setVisible(false);
        ui->pushButton_Prev->setVisible(false);

        ui->label_Title->setText("Finished Installation Successfully");
        ui->label_Para->setText("Congratulations! SH3 Dynamic Campaign has been installed successfully!\n\nThank you for playing SH3 Dynamic Campaign!");
        ui->label_Para->setVisible(true);

        ui->pushButton_Exit->setText("Finish");
        ui->pushButton_Exit->setVisible(true);
        ui->checkBox_Shortcut->setVisible(true);


    break;


    }


}

void MainWindow::on_pushButton_Prev_clicked()
{
    this->page--;

    switch (this->page){
    case 1:
        ui->textEdit->setVisible(false);
        ui->pushButton_Prev->setVisible(false);
        ui->label_Para->setVisible(true);
        ui->label_Title->setText("Introduction");
        ui->radioButton_Disagree->setVisible(false);
        ui->radioButton_Agree->setVisible(false);
        ui->pushButton_Next->setEnabled(true);
    break;

    case 2:
        //set visible elements for Disclaimer
        ui->label_Para->setVisible(false);

        ui->textEdit->setVisible(true);
        ui->pushButton_Prev->setVisible(true);
        ui->radioButton_Disagree->setVisible(true);
        ui->radioButton_Agree->setVisible(true);

        //other
        ui->label_Title->setText("Disclaimer");
        ui->textEdit->setReadOnly(true);

        ui->label_SH3Install->setVisible(false);
        ui->lineEdit_SH3Install->setVisible(false);
        ui->label_SH3Saves->setVisible(false);
        ui->lineEdit_SH3Saves->setVisible(false);
        ui->label_SH3Commander->setVisible(false);

        ui->lineEdit_SH3Commander->setVisible(false);
        ui->checkBox->setVisible(false);
        ui->treeWidget->setVisible(false);
        ui->label_installItems->setVisible(false);
        ui->pushButton_DirSaves->setVisible(false);
        ui->pushButton_DirSH3->setVisible(false);
        ui->pushButton_DirSH3Cmdr->setVisible(false);
    break;

    case 3:        
        ui->label_ProgressBar->setText("Rolling back...");
        QFile::remove(this->SH3ProgramFilesPath + "/SH3 Dynamic Campaign.exe");
        QDir dir(this->SH3ProgramFilesPath + "/SH3 Dynamic Campaign");
        dir.removeRecursively();
        ui->progressBar->setValue(0);
        ui->label_ProgressBar->setText("Finished uninstalling...");

        // Visible Items
        ui->label_ProgressBar->setVisible(false);
        ui->progressBar->setVisible(false);

        ui->label_Title->setText("Finished Installation Unsuccessfully");
        ui->label_Para->setText("SH3 Dynamic Campaign components where not installed.");
        ui->label_Para->setVisible(true);
        ui->pushButton_Prev->setVisible(false);
        ui->pushButton_Exit->setVisible(true);

    break;

    }
}



void MainWindow::on_radioButton_Disagree_clicked()
{
    ui->pushButton_Next->setDisabled(true);
}

void MainWindow::on_radioButton_Agree_clicked()
{
    ui->pushButton_Next->setDisabled(false);
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked) {
        ui->label_SH3Commander->setEnabled(true);
        ui->lineEdit_SH3Commander->setEnabled(true);
        ui->pushButton_DirSH3Cmdr->setEnabled(true);
    }
    else {
        ui->label_SH3Commander->setEnabled(false);
        ui->lineEdit_SH3Commander->setEnabled(false);
        ui->pushButton_DirSH3Cmdr->setEnabled(true);
    }
}


void MainWindow::treeWidget(QTreeWidgetItem* fullPack, QTreeWidgetItem* sh3dc_FullPack, QTreeWidgetItem* captainsJournal_FullPack, QTreeWidgetItem* sh3dc, QTreeWidgetItem* captainsJournal){

    ui->treeWidget->setHeaderLabel("SH3 Dynamic Campaign - Install Packages");
    ui->treeWidget->setVisible(false);

    // Set treewidget items
    QDir sh3dcFullDir("SH3 Dynamic Campaign - Full");

    // SH3DC Full Install Package tree widget items
    if (sh3dcFullDir.exists()) {
       fullPack->setText(0, "SH3 Dynamic Campaign - Full Install Package");
       fullPack->setFlags(fullPack->flags() | Qt::ItemIsUserCheckable);
       fullPack->setCheckState(0, Qt::Checked);
       ui->treeWidget->addTopLevelItem(fullPack);

        // SH3DC - Full Package tree widget item
       //SH3DC of Full Package
       QDir sh3dc_FullDir("SH3 Dynamic Campaign - Full/SH3 Dynamic Campaign");
       if (sh3dc_FullDir.exists()) {
           sh3dc_FullPack->setText(0, "SH3 Dynamic Campaign");
           sh3dc_FullPack->setFlags(sh3dc_FullPack->flags() | Qt::ItemIsUserCheckable);
           sh3dc_FullPack->setCheckState(0, Qt::Checked);
           fullPack->addChild(sh3dc_FullPack);
       }

        // Captains Journal - Full Package tree widget item
       QDir captainsJournal_FullDir("SH3 Dynamic Campaign - Full/Captains Journal");
       if (captainsJournal_FullDir.exists()) {
           captainsJournal_FullPack->setText(0, "Captains Journal");
           captainsJournal_FullPack->setFlags(captainsJournal_FullPack->flags() | Qt::ItemIsUserCheckable);
           captainsJournal_FullPack->setCheckState(0, Qt::Checked);
           fullPack->addChild(captainsJournal_FullPack);
       }
    }
    else {
         // SH3DC Standalone Package tree widget item
         QDir sh3dcDir("SH3 Dynamic Campaign");
         if (sh3dcDir.exists()) {
            sh3dc->setText(0, "SH3 Dynamic Campaign - Standalone Package");
            sh3dc->setFlags(sh3dc->flags() | Qt::ItemIsUserCheckable);
            sh3dc->setCheckState(0, Qt::Checked);
            ui->treeWidget->addTopLevelItem(sh3dc);
         }

         // Captains Journal Standalone Package tree widget item
         QDir captainsJournal_Dir("Captains Journal");
         if (captainsJournal_Dir.exists()) {
           captainsJournal->setText(0, "Captain's Journal - Standalone Package");
           captainsJournal->setFlags(captainsJournal->flags() | Qt::ItemIsUserCheckable);
           captainsJournal->setCheckState(0, Qt::Checked);
           ui->treeWidget->addTopLevelItem(captainsJournal);
         }
    }
    ui->treeWidget->expandAll();
}


void MainWindow::checkIfExists(QString* sh3Dir, QString* profiles, QString* sh3Cmdr) {

    // Check if files entered exist

    // Check if sh3.exe file exists in path entered
    if (!(QFile::exists(*sh3Dir) && QFile::exists(*sh3Dir+"/sh3.exe")))  {
        QMessageBox sh3FileNotExist;
        sh3FileNotExist.setIcon(QMessageBox::Warning);
        sh3FileNotExist.setWindowTitle("Silent Hunter III");
        sh3FileNotExist.setText("The Silent Hunter III game executable \"sh3.exe\" cannot be found in that directory!");
        sh3FileNotExist.exec();
        this->page=3;
    }

    // Check if SH3 save game directory exists in path entered
    if (!(QFile::exists(*profiles) && QFile::exists(*profiles+"/data")))  {
        QMessageBox sh3SavesFolderNotExist;
        sh3SavesFolderNotExist.setIcon(QMessageBox::Warning);
        sh3SavesFolderNotExist.setWindowTitle("SH3 Saves Folder");
        sh3SavesFolderNotExist.setText("That is not the directory for SH3 saved game files!");
        sh3SavesFolderNotExist.exec();
        this->page=3;
    }


    // Check if SH3Cmdr.exe exists in path entered
    if (!(QFile::exists(*sh3Cmdr) && QFile::exists(*sh3Cmdr+"/sh3Cmdr.exe")) && (ui->checkBox->checkState() != 0 ))  {
        QMessageBox sh3CmdrFileNotExist;
        sh3CmdrFileNotExist.setIcon(QMessageBox::Warning);
        sh3CmdrFileNotExist.setWindowTitle("SH3 Commander");
        sh3CmdrFileNotExist.setText("The SH3 Commander executable \"SH3Cmdr.exe\" cannot be found in that directory!");
        sh3CmdrFileNotExist.exec();
        this->page=3;
    }
}


void MainWindow::launchBat(QString* batPath) {

    // Start batch file to perform other duties
    QProcess p;
    QStringList abc;
    abc << "/C" << *batPath;

    for (int x=26;x < 51;x++) {
        ui->progressBar->setValue(x);
    }

    ui->label_ProgressBar->setText("Installing SH3 Dynamic Camnpaign...");
    p.startDetached("cmd.exe", abc);

    for (int x=51;x < 76;x++) {
        ui->progressBar->setValue(x);
    }
    ui->label_ProgressBar->setText("Finishing Installation...");
}


//unzip resource files
void MainWindow::unzip() {
    QProcess p;
    QStringList abc;
    QString unzipper = "unzipper.bat";
    QFile file(":/Installation_Files/unzipper.bat");
    QFile test("unzipper.bat");
    if(!test.exists()) {
        file.copy("unzipper.bat");
    }
    file.close();
    QString zipFile = "SH3 Dynamic Campaign - Full.zip";
    file.setFileName(":/Installation_Files/SH3 Dynamic Campaign - Full.zip");
    test.setFileName("SH3 Dynamic Campaign - Full.zip");
    if(!test.exists()) {
        file.copy("SH3 Dynamic Campaign - Full.zip");
    }
    file.close();
    test.close();

    QDir dirTest("SH3 Dynamic Campaign - Full");
    if(!dirTest.exists()) {
        QString unzipDestination = QDir::currentPath();
        abc << "/C" << "start" << "/min" << unzipper << zipFile << unzipDestination << "^&" << "exit";
        p.startDetached("cmd.exe", abc);

        wDialog = new WaitDialog();
        wDialog->setWindowFlags(Qt::WindowStaysOnTopHint);
        wDialog->show();

        //QObject::connect(watcher, SIGNAL(fileChanged(const QString&)), this, SLOT(wait_dialog_box(const QString&)));

        //QTimer::singleShot(2000, this, SLOT(wait_dialog_box(const QString&)));

        QTimer::singleShot(13000, this, SLOT(installation_directory_page()));

        QTimer::singleShot(14000, wDialog, SLOT(close_Dialog()));

        /*
        QMutex mut;
        mut.lock();
        mut.tryLock(8000);
        mut.unlock();
        */





    }

}

//remove unzipped temp install files
void MainWindow::delTempFiles() {

    QFile file(QDir::currentPath()+"/unzipper.bat");
    file.setPermissions(QFile::ReadOther | QFile::WriteOther);
    if(!file.remove()) {
        qDebug() << "File unzipper.bat could not be deleted";
        QMessageBox::warning(this, "COULD NOT DELETE FILE","Could not delete temporary file: '" + file.fileName() + "'");
    }

    file.setFileName("SH3 Dynamic Campaign - Full.zip");
    file.setPermissions(QFile::ReadOther | QFile::WriteOther);
    if(!file.remove()) {
        qDebug() << "File 'SH3 Dynamic Campaign - Full.zip' could not be deleted";
        QMessageBox::warning(this, "COULD NOT DELETE FILE","Could not delete temporary file: '" + file.fileName() + "'");
    }
    file.close();

    QMutex mut;
    mut.lock();
    mut.tryLock(1500);
    mut.unlock();

    QDir sh3DCTemp("SH3 Dynamic Campaign - Full");
    if(sh3DCTemp.exists()) {
        if(!sh3DCTemp.removeRecursively()) {
            qDebug() << "Directory 'SH3 Dynamic Campaign - Full' could not be deleted";
            QMessageBox::warning(this, "COULD NOT DELETE DIRECTORY","Could not delete directory: '" + sh3DCTemp.absolutePath() + "'");
        }
    }
}


void MainWindow::outputPaths(QString* SH3ProgramFilesPath, QString* userProfilePath, QString* SH3CommanderPath) {

    // Open output file to output path variables
    QDir sh3dcFullDir("SH3 Dynamic Campaign - Full");

    if (sh3dcFullDir.exists())  {
        QDir sh3dc_FullDir("SH3 Dynamic Campaign - Full/SH3 Dynamic Campaign");

        if (sh3dc_FullDir.exists()) {
            QDir dataDir;
            if (!dataDir.mkpath("SH3 Dynamic Campaign - Full/SH3 Dynamic Campaign/Dynamic Campaign/DATA")) {
                    QMessageBox::warning(this, "CANNOT MAKE DIRECTORY","Cannot make directory: '" + dataDir.absolutePath() + "'");

            }

            QFile file("SH3 Dynamic Campaign - Full/SH3 Dynamic Campaign/Dynamic Campaign/DATA/settings.txt");
            if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
                 qDebug() << "Error: Cannot open file: " << file.fileName();
                 QMessageBox::warning(this, "CANNOT OPEN FILE","Cannot open file: '" + file.fileName() + "'");

            }
            else {
                 QTextStream stream(&file);
                 stream << "[PATHS]" << endl;
                 stream << "sh3Directory=" << *SH3ProgramFilesPath << endl;
                 stream << "sh3Saves=" << *userProfilePath << endl;
                 if(ui->checkBox->isChecked()) {
                    stream << "sh3Commander=" << *SH3CommanderPath << endl;
                 }
                 else {
                     stream << "sh3Commander=" << endl;
                 }
                 file.close();
            }        
        }
    }
}


void MainWindow::updateChecks(QTreeWidgetItem* item, int column) {
    bool diff = false;
    if(column != 0 && column!=-1)
        return;
    if(item->childCount()!=0 && item->checkState(0)!=Qt::PartiallyChecked && column!=-1){
        Qt::CheckState checkState = item->checkState(0);
        for (int i = 0; i < item->childCount(); ++i) {
           item->child(i)->setCheckState(0, checkState);
        }
    } else if (item->childCount()==0 || column==-1) {
        if(item->parent()==0)
            return;
        for (int j = 0; j < item->parent()->childCount(); ++j) {
            if(j != item->parent()->indexOfChild(item) && item->checkState(0)!=item->parent()->child(j)->checkState(0)){
                diff = true;
            }
        }
        if(diff)
            item->parent()->setCheckState(0,Qt::PartiallyChecked);
        else
            item->parent()->setCheckState(0,item->checkState(0));
        if(item->parent()!=0)
            updateChecks(item->parent(),-1);
    }
}


void MainWindow::on_pushButton_Exit_clicked()
{

    if (ui->checkBox_Shortcut->isChecked() && this->page==4) {
        QProcess q;
        QStringList stringList;
        stringList << "/C" << "start" << "/min" << "" << "SH3 Dynamic Campaign - Full/SH3 Dynamic Campaign/Create Shortcut.bat" << "^&" << "exit";
        q.startDetached("cmd.exe", stringList);


    }

    delTempFiles();
    wDialog = new WaitDialog();
    wDialog->setWindowFlags(Qt::WindowStaysOnTopHint);
    wDialog->show();

    QTimer::singleShot(500, this, SLOT(close_Mainwindow()));
    QTimer::singleShot(500, wDialog, SLOT(close_Dialog()));


}

void MainWindow::on_pushButton_DirSH3_clicked()
{
    //Open dialog with folder path filters.
    QString folder = dialog.getExistingDirectory(this, tr("Find Silent Hunter III installation folder"),ui->lineEdit_SH3Install->text(),QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    //QString folder = dialog.getOpenFileName(this,tr("Find the Silent Hunter III folder"), filepath, tr("Silent Hunter III Installation Directory (*)"));
    if(folder != NULL) {
        ui->lineEdit_SH3Install->setText(folder);
    }
}

void MainWindow::on_pushButton_DirSaves_clicked()
{
    //Open dialog with filepath and filename filters.
    QString folder = dialog.getExistingDirectory(this, tr("Find SH3 save game folder"),ui->lineEdit_SH3Saves->text(),QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    //QString folder = dialog.getOpenFileName(this,tr("Find the SH3 save game folder"), filepath, tr("SH3 Save Game Folder (*)"));
    if(folder != NULL) {
        ui->lineEdit_SH3Saves->setText(folder);
    }
}

void MainWindow::on_pushButton_DirSH3Cmdr_clicked()
{
    //Open dialog with filepath and filename filters.
    QString folder = dialog.getExistingDirectory(this, tr("Find SH3 Commander installation directory"),ui->lineEdit_SH3Commander->text(),QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    //QString folder = dialog.getOpenFileName(this,tr("Find the SH3 Commander installation directory"), filepath, tr("SH3 Commander Installation Directory (*)"));
    if(folder != NULL) {
        ui->lineEdit_SH3Commander->setText(folder);
    }
}

void MainWindow::installation_directory_page()
{

    treeWidget(fullPack, sh3dcFullPack, captainsJournal_FullPack, sh3dc, captainsJournal);

    ui->textEdit->setVisible(false);
    ui->radioButton_Disagree->setVisible(false);
    ui->radioButton_Agree->setVisible(false);

    ui->label_SH3Install->setVisible(true);
    ui->lineEdit_SH3Install->setVisible(true);
    ui->label_SH3Saves->setVisible(true);
    ui->lineEdit_SH3Saves->setVisible(true);
    ui->label_SH3Commander->setVisible(true);
    ui->lineEdit_SH3Commander->setVisible(true);
    ui->checkBox->clicked(false);
    ui->checkBox->setVisible(true);
    ui->treeWidget->setVisible(true);
    ui->label_installItems->setVisible(true);
    ui->treeWidget->setVisible(true);
    ui->pushButton_DirSaves->setVisible(true);
    ui->pushButton_DirSH3->setVisible(true);
    ui->pushButton_DirSH3Cmdr->setVisible(true);

    // Title
    ui->label_Title->setText("Installation Directories");

    // Line edits
    ui->lineEdit_SH3Install->setText(SH3ProgramFilesPath);
    ui->lineEdit_SH3Saves->setText(fullUserProfilePath);
    ui->lineEdit_SH3Saves->setMinimumWidth((ui->lineEdit_SH3Saves->text()).length()+3);

    // SH3Cmdr line edits (depends on checkbox)
    if(!ui->checkBox->isChecked()) {
        ui->label_SH3Commander->setDisabled(true);
        ui->lineEdit_SH3Commander->setDisabled(true);
        ui->pushButton_DirSH3Cmdr->setDisabled(true);
    } else {
        ui->label_SH3Commander->setDisabled(false);
        ui->lineEdit_SH3Commander->setDisabled(false);
        ui->pushButton_DirSH3Cmdr->setDisabled(false);
     }

    ui->lineEdit_SH3Commander->setText(SH3CommanderPath);

}


void MainWindow::close_Mainwindow()
{
    this->close();
}
