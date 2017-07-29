#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H


#include "grabdata.h"
#include "externalprograms.h"

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    void Populate();
    void Load();
    bool checkIfExists(QString, QString, QString, QString);


private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void on_btnApply_clicked();

    void on_chBoxSubmarineTrackingRoom_toggled(bool checked);

    void on_btnSubmarineTrackingRoom_clicked();

    void on_btnSh3dir_clicked();

    void on_btnSh3Saves_clicked();

    void on_btnSh3Cmdr_clicked();

    void on_chBoxSh3Commander_toggled(bool checked);

    void on_txtSh3Directory_textEdited(const QString&);

    void on_txtSh3Saves_textEdited(const QString&);

    void on_txtSh3Commander_textEdited(const QString&);

    void on_txtSubmarineTrackingRoom_textEdited(const QString&);

    void on_chBoxSh3Commander_clicked(bool checked);

    void on_chBoxSubmarineTrackingRoom_clicked(bool checked);

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
