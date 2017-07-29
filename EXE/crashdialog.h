#ifndef CRASHDIALOG_H
#define CRASHDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "batch.h"


namespace Ui {
class CrashDialog;
}

class CrashDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CrashDialog(QWidget *parent = 0);
    ~CrashDialog();
    QMessageBox *info;


private slots:
    void on_pushButton_Proceed_clicked();
    void on_pushButton_Cancel_clicked();  
    void scriptStatusFileChanged_crashObj(const QString&);

private:
    Ui::CrashDialog *ui;
};

#endif // CRASHDIALOG_H
