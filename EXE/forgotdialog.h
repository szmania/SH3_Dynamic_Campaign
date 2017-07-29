#ifndef FORGOTDIALOG_H
#define FORGOTDIALOG_H


#include "grabdata.h"
#include "batch.h"

#include <QDialog>

namespace Ui {
class ForgotDialog;
}

class ForgotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ForgotDialog(QWidget *parent = 0);
    ~ForgotDialog();  
    void populateEntries(QString, QString);
    void getCareerNames(QString);
    void getPatrolNum(QString, QString);
    void getPatrolNum2(const QString*);
    void getSunkClass();
    QString getGrid(int);
    QString getDate(int);
    void disableFields(bool);

private slots:

    void on_comboCareer_currentIndexChanged(const QString &arg1);

    void on_comboPatrol_currentIndexChanged(int);

    void on_comboClass_currentIndexChanged(int index);

    void on_btnRun_clicked();

    void on_txtLong_textChanged(const QString &arg1);

    void on_txtLat_textChanged(const QString &arg1);



private:
    Ui::ForgotDialog *ui;


};

#endif // FORGOTDIALOG_H
