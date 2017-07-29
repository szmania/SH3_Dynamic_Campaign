//Program settings dialog box

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>


SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    Populate();
    Load();
    this->setAttribute(Qt::WA_DeleteOnClose);

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::Populate()
{
    GrabData *grabDataObj = new GrabData();
    //populate sh3directory box
    ui->txtSh3Directory->setText(grabDataObj->return_sh3Directory());
    //populate sh3saves box
    ui->txtSh3Saves->setText(grabDataObj->return_sh3Saves());
    //populate sh3commander box
    ui->txtSh3Commander->setText(grabDataObj->return_sh3Commander());
    //populate submarineTrackingRoom box
    ui->txtSubmarineTrackingRoom->setText(grabDataObj->return_submarineTrackingRoom());
}

void SettingsDialog::Load()
{
    GrabData *grabDataObj = new GrabData();
    ui->btnCancel->setEnabled(false);
    ui->btnApply->setEnabled(false);

    //check to see iSH3 Commander directory box is ticked
    if((grabDataObj->return_line("chBoxSh3Commander="))=="1") {
        ui->lblSh3Commander->setEnabled(true);
        ui->txtSh3Commander->setEnabled(true);
        ui->btnSh3Cmdr->setEnabled(true);
        ui->chBoxSh3Commander->setChecked(true);
    } else {
        ui->lblSh3Commander->setEnabled(false);
        ui->txtSh3Commander->setEnabled(false);
        ui->btnSh3Cmdr->setEnabled(false);
        ui->chBoxSh3Commander->setChecked(false);
    }



    //check to see if previous Submarine Tracking Room directory in settings.cfg
    if((grabDataObj->return_line("chBoxSubmarineTrackingRoom="))=="1") {
        ui->lblSubmarineTrackingRoom->setEnabled(true);
        ui->txtSubmarineTrackingRoom->setEnabled(true);
        ui->btnSubmarineTrackingRoom->setEnabled(true);
        ui->chBoxSubmarineTrackingRoom->setChecked(true);
    } else {
        ui->lblSubmarineTrackingRoom->setEnabled(false);
        ui->txtSubmarineTrackingRoom->setEnabled(false);
        ui->btnSubmarineTrackingRoom->setEnabled(false);
        ui->chBoxSubmarineTrackingRoom->setChecked(false);
    }


}

void SettingsDialog::on_btnOK_clicked()
{
    //MainWindow *mw = new MainWindow();
    //mw->sh3dc_page();
    this->close();

}

void SettingsDialog::on_btnCancel_clicked()
{
    this->close();
}



void SettingsDialog::on_btnApply_clicked()
{

    GrabData *grabDataObj = new GrabData();
    //disable Cancel and Apply buttons


    //export data
    if (checkIfExists("Silent Hunter III", "The Silent Hunter III game executable \"sh3.exe\" cannot be found in that directory!", ui->txtSh3Directory->text(), "sh3")) {
        grabDataObj->export_sh3Directory(ui->txtSh3Directory->text());
    }

    if (checkIfExists("SH3 Saves directory", "That is not the directory for SH3 saved game files!", ui->txtSh3Saves->text(), "")) {
        grabDataObj->export_sh3Saves(ui->txtSh3Saves->text());
    }

    if (ui->chBoxSh3Commander->isChecked()) {
        if (checkIfExists("SH3 Commander", "The SH3 Commander executable \"SH3Cmdr.exe\" cannot be found in that directory!", ui->txtSh3Commander->text(), "SH3Cmdr")) {
            grabDataObj->export_sh3Commander(ui->txtSh3Commander->text());
            grabDataObj->adjust_settings_value("DATA\\settings.cfg", "chBoxSh3Commander", "1");
        } else {
            grabDataObj->adjust_settings_value("DATA\\settings.cfg", "chBoxSh3Commander", "0");
        }
    } else {
        grabDataObj->adjust_settings_value("DATA\\settings.cfg", "chBoxSh3Commander", "0");
    }

    if (ui->chBoxSubmarineTrackingRoom->isChecked()) {

        if(!ui->chBoxSh3Commander->isChecked()) {
            QMessageBox chBoxSh3CommanderNotChecked;
            chBoxSh3CommanderNotChecked.setIcon(QMessageBox::Warning);
            chBoxSh3CommanderNotChecked.setWindowTitle("SH3 Commander required for SH3 Tracking Room");
            chBoxSh3CommanderNotChecked.setText("SH3 Commander box must be checked if SH3 Tracking Room box is checked.");
            chBoxSh3CommanderNotChecked.exec();
            ui->chBoxSubmarineTrackingRoom->setChecked(false);
        } else {

            if (checkIfExists("Submarine Tracking Room", "The Submarine Tracking Room executable \"Submarine Tracking Room V#.exe\" cannot be found in that directory!", ui->txtSubmarineTrackingRoom->text(), "")) {
                grabDataObj->export_submarineTrackingRoom(ui->txtSubmarineTrackingRoom->text());
                grabDataObj->adjust_settings_value("DATA\\settings.cfg", "chBoxSubmarineTrackingRoom", "1");
            } else {
                ui->chBoxSubmarineTrackingRoom->setChecked(false);
                grabDataObj->adjust_settings_value("DATA\\settings.cfg", "chBoxSubmarineTrackingRoom", "0");
            }
        }
    } else {
        grabDataObj->adjust_settings_value("DATA\\settings.cfg", "chBoxSubmarineTrackingRoom", "0");
    }

    ui->btnCancel->setEnabled(false);
    ui->btnApply->setEnabled(false);

}

bool SettingsDialog::checkIfExists(QString windowTitle, QString windowText, QString directory, QString executable) {

    // Check if files entered exist
    if (directory !="") {
        if (!(QFile::exists(directory))) {
                QMessageBox fileNotExist;
                fileNotExist.setIcon(QMessageBox::Warning);
                fileNotExist.setWindowTitle(windowTitle);
                fileNotExist.setText(windowText);
                fileNotExist.exec();
                return false;

        }

        if (executable!="") {
            if (!(QFile::exists(directory+"/"+executable+".exe"))) {
                QMessageBox fileNotExist;
                fileNotExist.setIcon(QMessageBox::Warning);
                fileNotExist.setWindowTitle(windowTitle);
                fileNotExist.setText(windowText);
                fileNotExist.exec();
                return false;
            }
        }

    }

    return true;
}

void SettingsDialog::on_chBoxSh3Commander_toggled(bool checked)
{
    if(checked) {
        ui->lblSh3Commander->setEnabled(true);
        ui->txtSh3Commander->setEnabled(true);
        ui->btnSh3Cmdr->setEnabled(true);
    }
    else if(!checked){
        ui->lblSh3Commander->setEnabled(false);
        ui->txtSh3Commander->setEnabled(false);
        ui->btnSh3Cmdr->setEnabled(false);
    }
}

void SettingsDialog::on_chBoxSubmarineTrackingRoom_toggled(bool checked)
{
    if(checked) {
        ui->lblSubmarineTrackingRoom->setEnabled(true);
        ui->txtSubmarineTrackingRoom->setEnabled(true);
        ui->btnSubmarineTrackingRoom->setEnabled(true);
    }
    else if(!checked){
        ui->lblSubmarineTrackingRoom->setEnabled(false);
        ui->txtSubmarineTrackingRoom->setEnabled(false);
        ui->btnSubmarineTrackingRoom->setEnabled(false);
    }
}




void SettingsDialog::on_btnSubmarineTrackingRoom_clicked()
{
    GrabData *grabDataObj = new GrabData();
    QFileDialog dialog;
    QString executable = dialog.getOpenFileName(this,tr("Find the Submarine Tracking Room executable"), grabDataObj->return_sh3Saves()+"\\data\\cfg", tr("*.exe"));
    if(executable != NULL) {
        ui->txtSubmarineTrackingRoom->setText(executable.replace("/","\\"));
    }
}

void SettingsDialog::on_btnSh3dir_clicked()
{
    //qDebug() << QByteArray::constData(qgetenv("PROGRAMFILES"));
    QFileDialog dialog;
    QString programFilesPath(getenv("PROGRAMFILES"));
    QString executable = dialog.getExistingDirectory(this,tr("Find the Silent Hunter III directory"), programFilesPath+"\\Ubisoft\\SilentHunterIII", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(executable != NULL) {
        ui->txtSh3Directory->setText(executable.replace("/","\\"));
    }
}

void SettingsDialog::on_btnSh3Saves_clicked()
{
    QFileDialog dialog;
    QString defaultUserProfile(getenv("DEFAULTUSERPROFILE"));

    QString executable = dialog.getExistingDirectory(this,tr("Find the Silent Hunter III saves directory"), defaultUserProfile+"\\SH3\\data\\cfg", QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if(executable != NULL) {
        ui->txtSh3Saves->setText(executable.replace("/","\\"));
    }

}

void SettingsDialog::on_btnSh3Cmdr_clicked()
{
    QFileDialog dialog;
    QString programFilesPath(getenv("PROGRAMFILES"));

    QString executable = dialog.getExistingDirectory(this,tr("Find the SH3 Commander directory"), programFilesPath+"\\SH3 Commander", QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if(executable != NULL) {
        ui->txtSh3Commander->setText(executable.replace("/","\\"));
    }

}

void SettingsDialog::on_txtSh3Directory_textEdited(const QString&)
{
    ui->btnCancel->setEnabled(true);
    ui->btnApply->setEnabled(true);
}

void SettingsDialog::on_txtSh3Saves_textEdited(const QString&)
{
    ui->btnCancel->setEnabled(true);
    ui->btnApply->setEnabled(true);
}

void SettingsDialog::on_txtSh3Commander_textEdited(const QString&)
{
    ui->btnCancel->setEnabled(true);
    ui->btnApply->setEnabled(true);
}

void SettingsDialog::on_txtSubmarineTrackingRoom_textEdited(const QString&)
{
    ui->btnCancel->setEnabled(true);
    ui->btnApply->setEnabled(true);
}

void SettingsDialog::on_chBoxSh3Commander_clicked(bool)
{
    ui->btnCancel->setEnabled(true);
    ui->btnApply->setEnabled(true);
}

void SettingsDialog::on_chBoxSubmarineTrackingRoom_clicked(bool)
{
    ui->btnCancel->setEnabled(true);
    ui->btnApply->setEnabled(true);
}
