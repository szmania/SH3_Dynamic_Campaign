#include "uninstalldialog.h"
#include "ui_uninstalldialog.h"

#include "batch.h"

#include <QMessageBox>
#include <QFile>

UninstallDialog::UninstallDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UninstallDialog)
{
    ui->setupUi(this);
}

UninstallDialog::~UninstallDialog()
{
    delete ui;
}

void UninstallDialog::on_pushButton_Proceed_clicked()
{
    Batch *batchObj = new Batch();
    batchObj->uninstall();

    this->close();
}

void UninstallDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}

void UninstallDialog::scriptStatusFileChanged_uninstallObj(const QString&)
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

        if (line.contains("SH3 Dynamic Campaign has been successfully uninstalled.") && (prevLine.contains("Uninstalling SH3 Dynamic Campaign."))) {
            QMessageBox *info = new QMessageBox(this);
            info->setIcon(QMessageBox::Information);
            info->setText("SH3 Dynamic Campaign has been successfully uninstalled.");
            info->setWindowTitle("SH3 Dynamic Campaign Uninstall Complete!");
            info->exec();

        }


    }
    file.close();
}
