#ifndef BACKUPDIALOG_H
#define BACKUPDIALOG_H

#include <QDialog>
#include "batch.h"

namespace Ui {
class BackupDialog;
}

class BackupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BackupDialog(QWidget *parent = 0);
    ~BackupDialog();

private slots:
    void on_pushButton_Proceed_clicked();
    void on_pushButton_Cancel_clicked();
    void scriptStatusFileChanged_backupObj(const QString&);


private:
    Ui::BackupDialog *ui;
};

#endif // BACKUPDIALOG_H
