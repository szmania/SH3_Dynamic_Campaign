#include "backupdialog.h"
#include "ui_backupdialog.h"
#include "batch.h"

#include <QFile>
#include <QDebug>
#include <QMessageBox>



BackupDialog::BackupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BackupDialog)
{
    ui->setupUi(this);

}

BackupDialog::~BackupDialog()
{
    delete ui;
}

void BackupDialog::on_pushButton_Proceed_clicked()
{
    Batch *batchObj = new Batch();
    batchObj->backup();
    this->close();
}

void BackupDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}

void BackupDialog::scriptStatusFileChanged_backupObj(const QString&)
{
    QFile file("TEMP/script_status.log");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.fileName() << file.errorString();
    } else {

        QTextStream in(&file);
        QString line;
        QString prevLine;



        while(!in.atEnd()) {
            prevLine = line;
            line = in.readLine();

        }

        if (line.contains("Exiting \"SH3_Dynamic_Campaign.exe\".") && (prevLine.contains("Backing up original Silent Hunter III campaign and"))) {
            QMessageBox *info = new QMessageBox(this);
            info->setIcon(QMessageBox::Information);
            info->setText("Stock Silent Hunter III campaign files and \"EnglishNames.cfg\", \"GermanNames.cfg\", and \"FrenchNames.cfg\" backup complete.");
            info->setWindowTitle("Backup Complete!");
            info->exec();
            //this, "Backup1 Complete!","Stock Silent Hunter III campaign files and \"EnglishNames.cfg\", \"GermanNames.cfg\", and \"FrenchNames.cfg\" backup complete.");
            //qDebug() << info->clickedButton()->text();

        }


    }
    file.close();
}
