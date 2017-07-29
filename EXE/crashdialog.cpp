#include "crashdialog.h"
#include "ui_crashdialog.h"
#include "batch.h"

#include <QMessageBox>
#include <QFile>

CrashDialog::CrashDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CrashDialog)
{
    ui->setupUi(this);
}

CrashDialog::~CrashDialog()
{
    delete ui;
}

void CrashDialog::on_pushButton_Proceed_clicked()
{
    Batch *batchObj = new Batch();
    batchObj->crash();
    this->close();
}

void CrashDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}

void CrashDialog::scriptStatusFileChanged_crashObj(const QString&)
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

        if (line.contains("Your SH3 Dynamic Campaign program has been recovered successfully from the crash.") && (prevLine.contains("Crash procedure is running."))) {
            QMessageBox *info = new QMessageBox(this);
            info->setIcon(QMessageBox::Information);
            info->setText("SH3 Dynamic Campaign and Silent Hunter III has recovered successfully from the crash.");
            info->setWindowTitle("Crash Recovery Complete!");
            info->exec();
            //qDebug() << info->clickedButton()->text();

        }


    }
    file.close();
}
