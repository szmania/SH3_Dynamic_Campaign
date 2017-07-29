#ifndef UNINSTALLDIALOG_H
#define UNINSTALLDIALOG_H

#include <QDialog>

#include "batch.h"


namespace Ui {
class UninstallDialog;
}

class UninstallDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UninstallDialog(QWidget *parent = 0);
    ~UninstallDialog();

private slots:
    void on_pushButton_Proceed_clicked();
    void on_pushButton_Cancel_clicked();
    void scriptStatusFileChanged_uninstallObj(const QString&);

private:
    Ui::UninstallDialog *ui;
};

#endif // UNINSTALLDIALOG_H
