//About program dialog box
#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->lblWebsite->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->lblWebsite->setOpenExternalLinks(true);
    this->setAttribute(Qt::WA_DeleteOnClose);

}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_pushButton_clicked()
{
    this->close();
}
