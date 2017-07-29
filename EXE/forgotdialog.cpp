//Forgot to mark ship dialog box

#include "forgotdialog.h"
#include "ui_forgotdialog.h"
#include "sh3dc_startup.h"

#include <QDebug>
#include <QDate>
#include <QMutex>

ForgotDialog::ForgotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForgotDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

ForgotDialog::~ForgotDialog()
{
    delete ui;

}


void ForgotDialog::populateEntries(QString CareerName, QString PatrolNum)
{
    ui->comboCareer->clear();

    //ui->txtCareer->setText(CareerName);
    //ui->comboPatrol->addItem(PatrolNum);
    getCareerNames(CareerName);
    ui->comboPatrol->clear();
    ui->comboClass->clear();
    getPatrolNum(CareerName, PatrolNum);
    //getSunkClass();
    ui->lblStatus->setAlignment(Qt::AlignCenter);
    ui->lblHeading->setAlignment(Qt::AlignCenter);
    ui->btnRun->setStyleSheet("padding: 4px;");
    ui->btnRun->setDisabled(true);

}

void ForgotDialog::getCareerNames(QString CareerName) {
//    QFile file("TEMP\\careers_patrols.tmp");

//    if (!file.open(QIODevice::ReadOnly)) {
//        qDebug() << file.fileName() << file.errorString();
//    }
//    else {

//        QTextStream in(&file);
//        QString line;
//        int lines = 0;

//        while(!in.atEnd()) {
//            lines++;

        sh3dc_startup *sh3dc_startupObj = new sh3dc_startup();
        QMap<QString, int> careerDirMap = sh3dc_startupObj->create_CareerDirs();

        for(int i = 0; i < careerDirMap.values().size(); ++i){
            qDebug() << careerDirMap.keys().at(i)  + "-" + QString::number(careerDirMap.values().at(i));
            QString line = careerDirMap.keys().at(i) + "-" + QString::number(careerDirMap.values().at(i));
//            line = in.readLine();
//            qDebug() << "line: " << line;

            QRegExp rx("\\-"); //RegEx for '-'


            QStringList query = line.split(rx);
            ui->comboCareer->addItem(query.value(0));
         }
//        file.close();

//    }

    if(ui->comboCareer->currentText() != CareerName) {
        ui->comboCareer->setCurrentText(CareerName);
    }
}

void ForgotDialog::getPatrolNum(QString CareerName, QString PatrolNum)
{
    if(PatrolNum.toInt() > 0) {
//        QFile file("TEMP\\careers_patrols.tmp");

//        if (!file.open(QIODevice::ReadOnly)) {
//            qDebug() << file.fileName() << file.errorString();
//        }
//        else {

//            QTextStream in(&file);
//            QString line;
//            int lines = 0;

//            while(!in.atEnd()) {
//                lines++;

//                line = in.readLine();
                //qDebug() << "line: " << line;
        sh3dc_startup *sh3dc_startupObj = new sh3dc_startup();
        QMap<QString, int> careerDirMap = sh3dc_startupObj->create_CareerDirs();
        for(int i = 0; i < careerDirMap.values().size(); ++i){
            qDebug() << careerDirMap.keys().at(i)  + "-" + QString::number(careerDirMap.values().at(i));
            QString line = careerDirMap.keys().at(i) + "-" + QString::number(careerDirMap.values().at(i));

            QRegExp rx("\\-"); //RegEx for '-'


            QStringList query = line.split(rx);
            if(query.value(0) == CareerName) {
                for (int i=0;i < query.value(1).toInt();i++) {
                    ui->comboPatrol->addItem(QString::number(i+1));
                }
            }

         }
//         }

        if(ui->comboPatrol->currentIndex() != PatrolNum.toInt()-1) {
            ui->comboPatrol->setCurrentIndex(PatrolNum.toInt()-1);
        }
//        file.close();
    }
}

void ForgotDialog::getPatrolNum2(const QString* CareerName)
{

//    QFile file("TEMP\\careers_patrols.tmp");

//    if (!file.open(QIODevice::ReadOnly)) {
//        qDebug() << file.fileName() << file.errorString();
//    }
//    else {

//    QTextStream in(&file);
//    QString line;
//    int lines = 0;

//    while(!in.atEnd()) {
//        lines++;

//        line = in.readLine();
//        //qDebug() << "line: " << line;
    sh3dc_startup *sh3dc_startupObj = new sh3dc_startup();
    QMap<QString, int> careerDirMap = sh3dc_startupObj->create_CareerDirs();
    for(int i = 0; i < careerDirMap.values().size(); ++i){
        qDebug() << careerDirMap.keys().at(i)  + "-" + QString::number(careerDirMap.values().at(i));
        QString line = careerDirMap.keys().at(i) + "-" + QString::number(careerDirMap.values().at(i));
        QRegExp rx("\\-"); //RegEx for '-'

        QStringList query = line.split(rx);
        if((query.value(0) == CareerName) && (query.value(1).toInt() > 0)) {
            for (int i=0;i < query.value(1).toInt();i++) {
                ui->comboPatrol->addItem(QString::number(i+1));
            }
        }
     }
//     }
//    file.close();
}

void ForgotDialog::getSunkClass()
{
    GrabData *grabDataObj = new GrabData();
    QFile file(grabDataObj->return_sh3Saves()+"/data/cfg/Careers/" + ui->comboCareer->itemText(ui->comboCareer->currentIndex()) + "/Log_" + QString::number(ui->comboPatrol->itemText(ui->comboPatrol->currentIndex()).toInt()-1) + ".cfg");
    if(!file.open(QIODevice::ReadOnly) && file.exists()) {
       qDebug() << file.errorString();
    }
    if(!file.exists()) {
       qDebug() << file.fileName() << "does not exist!";
    }

    QTextStream in(&file);
    QString line;
    while(!in.atEnd()) {
        line = in.readLine();
        if(!(line.indexOf("EntryText=Ship sunk!", 0, Qt::CaseSensitive)==-1)) {
            QRegExp rx("\\|"); //RegEx for '|'
            QStringList query = line.split(rx);
            QRegExp rxp("\\,"); //RegEx for ','
            QStringList query2 = query.value(2).split(rxp);
            ui->comboClass->addItem(query2.value(0));
        }
    }
    file.close();
    ui->comboClass->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    if(ui->comboClass->count()==0) {
        disableFields(true);
    } else {
        disableFields(false);
    }

}

QString ForgotDialog::getGrid(int index)
{
    GrabData *grabDataObj = new GrabData();
    QFile file(grabDataObj->return_sh3Saves()+"/data/cfg/Careers/" + ui->comboCareer->itemText(ui->comboCareer->currentIndex()) + "/Log_" + QString::number(ui->comboPatrol->itemText(ui->comboPatrol->currentIndex()).toInt()-1) + ".cfg");
    if(!file.open(QIODevice::ReadOnly) && file.exists()) {
       qDebug() << file.errorString();
    }
    if(!file.exists()) {
       qDebug() << file.fileName() << "does not exist!";
    }

    QTextStream in(&file);
    QString line;
    int count=0;
    while(!in.atEnd()) {
        line = in.readLine();
        if(!(line.indexOf("EntryText=Ship sunk!", 0, Qt::CaseSensitive)==-1) && (count==index)) {
            count++;
            QRegExp rx("\\|"); //RegEx for '|'
            QStringList query = line.split(rx);
            return (query.value(1));
        }
    }
    file.close();
    return 0;
    //ui->comboClass->setSizeAdjustPolicy(QComboBox::AdjustToContents);

}

QString ForgotDialog::getDate(int index)
{
    GrabData *grabDataObj = new GrabData();
    QFile file(grabDataObj->return_sh3Saves()+"/data/cfg/Careers/" + ui->comboCareer->itemText(ui->comboCareer->currentIndex()) + "/Log_" + QString::number(ui->comboPatrol->itemText(ui->comboPatrol->currentIndex()).toInt()-1) + ".cfg");
    if(!file.open(QIODevice::ReadOnly) && file.exists()) {
       qDebug() << file.errorString();
    }
    if(!file.exists()) {
       qDebug() << file.fileName() << "does not exist!";
    }

    QTextStream in(&file);
    QString line;
    int count=0;
    while(!in.atEnd()) {
        line = in.readLine();
        if(!(line.indexOf("EntryText=Ship sunk!", 0, Qt::CaseSensitive)==-1) && (count==index)) {
            while(!in.atEnd()) {
                count++;
                line = in.readLine();
                if(!(line.indexOf("EntryTitle=", 0, Qt::CaseSensitive)==-1)) {
                    QRegExp rx("\\,"); //RegEx for ','
                    QStringList query = line.split(rx);
                    QRegExp rxp("\\="); //RegEx for ','
                    QStringList query2 = query.value(0).split(rxp);

                    QString string = (query2.value(1)) + "," + (query.value(1));
                    QDate date(QDate::fromString(string, "MMMM d, yyyy"));
                    file.close();
                    return date.toString("yyyyMMdd");
                }
            }
        }
    }
    file.close();
    //ui->comboClass->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    return 0;
}

void ForgotDialog::on_comboCareer_currentIndexChanged(const QString &arg1)
{
    ui->comboPatrol->clear();
    getPatrolNum2(&arg1);
    ui->comboClass->clear();
    getSunkClass();
}

void ForgotDialog::on_comboPatrol_currentIndexChanged(int)
{
    ui->comboClass->clear();
    getSunkClass();
}

void ForgotDialog::on_comboClass_currentIndexChanged(int index)
{
    if(index!=-1){
        ui->txtLong->setToolTip("Somewhere in " + getGrid(index) + "<br/>Example: \"980600.00\"");
        ui->txtLat->setToolTip("Somewhere in " + getGrid(index) + "<br/>Example: \"6444573.00\"");
        ui->lblLong->setToolTip("Somewhere in " + getGrid(index) + "<br/>Example: \"980600.00\"");
        ui->lblLat->setToolTip("Somewhere in " + getGrid(index) + "<br/>Example: \"6444573.00\"");
    } else {
    }
}

void ForgotDialog::disableFields(bool value) {
    ui->lblClass->setDisabled(value);
    ui->comboClass->setDisabled(value);
    ui->lblDate->setDisabled(value);
    ui->txtDate->setDisabled(value);
    ui->lblLong->setDisabled(value);
    ui->txtLong->setDisabled(value);
    ui->lblLat->setDisabled(value);
    ui->txtLat->setDisabled(value);


    if(value==true) {
        ui->comboClass->clear();
        ui->txtDate->clear();
        ui->txtLong->clear();
        ui->txtLat->clear();
        ui->txtLong->setToolTip("");
        ui->txtLat->setToolTip("");
        ui->lblLong->setToolTip("");
        ui->lblLat->setToolTip("");
        ui->lblStatus->setText("No sunken ships found in this patrol!");
    } else {
       ui->txtDate->setText(getDate(ui->comboClass->currentIndex()));
       ui->lblStatus->setText("Press \"Run DC Script\" when Long. and Lat. have been entered.");
    }

}

void ForgotDialog::on_btnRun_clicked()
{
    Batch *batchObj = new Batch();
    ui->lblStatus->setText("Let the script run. It will close when done.");
    batchObj->forgotMark(ui->comboCareer->itemText(ui->comboCareer->currentIndex()), ui->comboPatrol->itemText(ui->comboPatrol->currentIndex()), ui->comboClass->currentText(), ui->txtDate->text(), QString::number(ui->txtLong->text().toInt()), QString::number(ui->txtLat->text().toInt()));
    QMutex mut;
    mut.lock();
    mut.tryLock(2500);
    mut.unlock();
    this->close();
}

void ForgotDialog::on_txtLong_textChanged(const QString &arg1)
{
    if((ui->txtLat->text()!=NULL) && (arg1!=NULL)) {
       ui->btnRun->setDisabled(false);
    } else {
        ui->btnRun->setDisabled(true);
    }
}

void ForgotDialog::on_txtLat_textChanged(const QString &arg1)
{
    if((ui->txtLong->text()!=NULL) && (arg1!=NULL)) {
       ui->btnRun->setDisabled(false);
    } else {
        ui->btnRun->setDisabled(true);
    }
}


