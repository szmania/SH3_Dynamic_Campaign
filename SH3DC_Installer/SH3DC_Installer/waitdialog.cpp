#include "waitdialog.h"
#include "ui_waitdialog.h"

#include <QtCore>


WaitDialog::WaitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitDialog)
{
    ui->setupUi(this);
    setWindowFlags( Qt::CustomizeWindowHint );

}

WaitDialog::~WaitDialog()
{
    delete ui;
}

void WaitDialog::close_Dialog()
{
    close();
}
