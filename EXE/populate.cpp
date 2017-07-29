//Populate SH3 Dynamic campaign tab

#include "mainwindow.h"
#include "populate.h"

#include <QPushButton>
#include <QGridLayout>
#include <QFile>
#include <QDebug>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QRadioButton>
#include <QDir>
#include <QButtonGroup>
#include <QMessageBox>


Populate::Populate(QObject *parent) :
    QObject(parent)
{

}

Populate::~Populate(){


    delete btnCareer;
    delete btnRefresh;
    delete NewCareerCheckBox;
    delete NewCareerLineEdit;
    delete CareersTW_Patrols;
    delete patrol_Tab;
    delete SH3DC_Type;
    delete radSH3DCEasy;
    delete radSH3DCOriginal;
    delete btnShowMarksFile;
    delete lblMarksExample;
    delete lblForgotMark;
    //delete SH3DC_Type_NC;
    delete radSH3DCEasy_NC;

}

void Populate::careerTab(QWidget *tab, QString line)
{
    SavesData *savesDataObj = new SavesData();

    QGridLayout *layout = new QGridLayout;

    QRegExp rx("\\-"); //RegEx for '-'
    QStringList query = line.split(rx);
    create_CareersTW_Patrols(tab, layout, (query.value(1)).toInt(),query.value(0));

    create_btnCareer(tab, layout);
    create_btnScriptsOnly(tab, layout);
    create_btnRefresh(tab, layout);

    sunkData(query.value(0), tab, layout, query.value(1).toInt());


    create_LabelPair("<b>Start date:</b>", savesDataObj->career_StartDate(query.value(0)), 2, 0, Qt::AlignLeft, layout, tab, NULL, false);

    tab->setLayout(layout);

    create_NewCareerBox(layout, tab);
    create_radSH3DCEasy(layout, tab);
    create_radSH3DCOriginal(layout, tab);
    create_btnShowMarksFile(layout, tab);
    create_lblMarksExample(layout, tab);
    create_lblForgotMark(layout, tab);

}

void Populate::newCareerTab(QWidget *tab)
{

    GrabData *grabDataObj = new GrabData();

    QGridLayout *gridLayout = new QGridLayout;
    QSpacerItem *spacerV = new QSpacerItem(1,450);
    gridLayout->addItem(spacerV,10,1);
    QSpacerItem *spacerH = new QSpacerItem(420,1);
    gridLayout->addItem(spacerH,1,10);
    QSpacerItem *spacerV2 = new QSpacerItem(1,20);
    gridLayout->addItem(spacerV2,2,1);

    QLabel *lblNewCareer = new QLabel;
    lblNewCareer->setText("New Career Name:");
    gridLayout->addWidget(lblNewCareer, 1, 1, Qt::AlignRight);
    txtNewCareer = new QLineEdit;
    txtNewCareer->setObjectName("txtNewCareer");
    gridLayout->addWidget(txtNewCareer, 1, 2, Qt::AlignLeft);


    QHBoxLayout *layoutH2 = new QHBoxLayout;
    QButtonGroup *SH3DC_Type_NC = new QButtonGroup(tab);
    radSH3DCEasy_NC = new QRadioButton(tab);
    radSH3DCEasy_NC->setObjectName("radSH3DCEasy_NC");
    SH3DC_Type_NC->addButton(radSH3DCEasy_NC);
    radSH3DCEasy_NC->setText("SH3 Dynamic Campaign EASY");
    gridLayout->addWidget(radSH3DCEasy_NC, 3, 2, Qt::AlignLeft);

    if((grabDataObj->return_line("radSH3DCEasy_NC="))=="0") {
        radSH3DCEasy_NC->setChecked(false);
    } else {
        radSH3DCEasy_NC->setChecked(true);
    }

    radSH3DCOriginal_NC = new QRadioButton(tab);
    radSH3DCOriginal_NC->setObjectName("radSH3DCOriginal_NC");
    SH3DC_Type_NC->addButton(radSH3DCOriginal_NC);
    radSH3DCOriginal_NC->setText("SH3 Dynamic Campaign ORIGINAL");
    layoutH2->addWidget(radSH3DCOriginal_NC);
    gridLayout->addWidget(radSH3DCOriginal_NC, 3, 3, Qt::AlignLeft);

    if((grabDataObj->return_line("radSH3DCOriginal_NC="))=="1") {
        radSH3DCOriginal_NC->setChecked(true);
    } else {
        radSH3DCOriginal_NC->setChecked(false);
    }



    tab->setLayout(gridLayout);

}

void Populate::create_CareersTW_Patrols(QWidget *tab, QGridLayout *layout, int numOfPatrols, QString career) {
    CareersTW_Patrols = new QTabWidget(tab);
    layout->addWidget(CareersTW_Patrols,4,0,10,21);


    QFile file("Careers/" + career + "/ShipSunk_Data.txt");


    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.fileName() << file.errorString();
    }

    for(int i=1 ; i < numOfPatrols+1; i++){
        QGridLayout *Pat_layout = new QGridLayout;
        patrol_Tab = new QWidget(CareersTW_Patrols);
        CareersTW_Patrols->setObjectName("CareersTW_Patrols");
        //qDebug() << "number of patrols: " << numOfPatrols;
        CareersTW_Patrols->addTab(patrol_Tab, "Patrol " + QString::number(i));
        patrol_Tab->setObjectName(career + "-" + QString::number(i));


        create_patrolTabData(Pat_layout, patrol_Tab, career, i, &file);

        patrol_Tab->setLayout(Pat_layout);

        Table *tableObj = new Table();
        tableObj->create_PatTable(patrol_Tab, numberSunk(&file, "Patrol=" + QString::number(i)), Pat_layout, career, QString::number(i));

     }

        file.close();



}


void Populate::create_btnCareer(QWidget *tab, QGridLayout *layout) {
    GrabData *grabDataObj = new GrabData();

    btnCareer = new QPushButton(tab);
    btnCareer->setObjectName("btnCareer");
    layout->addWidget(btnCareer,20,20,Qt::AlignRight|Qt::AlignBottom);
    btnCareer->setText("Start Career");
    btnCareer->setStyleSheet("QPushButton { font-weight: bold; padding: 7px; }");

    if (grabDataObj->return_line("chBoxSubmarineTrackingRoom=")=="1") {
        btnCareer->setText("Start \nSubmarine \nTracking Room");
    } else if(grabDataObj->return_line("chBoxSh3Commander=")=="1") {
        btnCareer->setText("Start \nSH3 Commander");
    }
}

void Populate::create_btnScriptsOnly(QWidget *tab, QGridLayout *layout) {
    btnScriptsOnly = new QPushButton(tab);
    btnScriptsOnly->setObjectName("btnScriptsOnly");
    layout->addWidget(btnScriptsOnly,18,20,Qt::AlignCenter);
    btnScriptsOnly->setText("Run Script Only");
    btnScriptsOnly->setStyleSheet("QPushButton { padding: 5px; }");
}

void Populate::create_btnRefresh(QWidget *tab, QGridLayout *layout) {
    btnRefresh = new QPushButton(tab);
    btnRefresh->setObjectName("btnRefresh");
    layout->addWidget(btnRefresh,0,20,Qt::AlignRight|Qt::AlignBottom);
    btnRefresh->setText("Refresh");
}

void Populate::sunkData(QString career, QWidget *tab, QGridLayout *layout, int numOfPatrols) {

    QFile file("Careers/" + career + "/ShipSunk_Data.txt");
    if(file.exists()){
        if(!file.open(QIODevice::ReadOnly)) {
            qDebug() << file.fileName() << file.errorString();
        } else{

            QTextStream in(&file);
            QString line;
            int lines = 0;

            while(!in.atEnd()) {
                lines++;
                line = in.readLine();
                //qDebug() << "line: " << line;
            }
        }
        file.close();
    }

    create_LabelPair("<font size=\"5\"><b>Career:</b></font>", "<font size=\"5\">"+career+"</font>", 0, 0, Qt::AlignTop|Qt::AlignLeft, layout, tab, NULL, false);


    int numSunkSH3DC = numberSunk(&file, "Career=" + career);
    int numSunkNonSH3DC = numberSunk_nonSH3DC(career, NULL, numOfPatrols);



    if(numSunkSH3DC < numSunkNonSH3DC) {
        if (numSunkNonSH3DC > 1) {
            create_LabelPair("<b>Total ships sunk:</b>", QString::number(numSunkSH3DC)+"  " + "<a href=\"http://google.com\">" + "<img src=\"://images/warning-icon.png\" width=\"20\" height=\"20\"\">" + "</a>" , 1, 0, Qt::AlignLeft, layout, tab, "SH3DC has found " + QString::number(numSunkNonSH3DC) +" ships, but has processed "+ QString::number(numSunkSH3DC) + " of them." +"\n It is recommended that you run the SH3DC scripts.", false);
        } else{
            create_LabelPair("<b>Total ships sunk:</b>", QString::number(numSunkSH3DC)+"  " + "<a href=\"http://google.com\">" + "<img src=\"://images/warning-icon.png\" width=\"20\" height=\"20\"\">" + "</a>" , 1, 0, Qt::AlignLeft, layout, tab, "SH3DC has found " + QString::number(numSunkNonSH3DC) +" ship, but has processed "+ QString::number(numSunkSH3DC) + " of them." +"\n It is recommended that you run the SH3DC scripts.", false);
        }
    } else{
        create_LabelPair("<b>Total ships sunk:</b>", QString::number(numSunkSH3DC), 1, 0, Qt::AlignLeft, layout, tab, NULL, false);

    }
    //qDebug() << career << "-" << numSunkNonSH3DC;
    file.close();


}

int Populate::numberSunk(QFile *file, QString find) {


    int sunkCount;

    if(file->exists()){
        if(file->isOpen()) {
            QTextStream in(file);
            QString all;
            all = in.readAll();
            sunkCount = all.count(find,Qt::CaseSensitive);
            file->close();
            return sunkCount;
        } else{

            if(!file->open(QIODevice::ReadOnly)) {
                qDebug() << file->fileName() << file->errorString();
            } else{
                QTextStream in(file);
                QString all;
                all = in.readAll();
                sunkCount = all.count(find,Qt::CaseSensitive);
                file->close();
                return sunkCount;
            }
        }
        file->close();
    }
    return 0;
}

void Populate::create_LabelPair(QString label, QString value, int row, int col, Qt::Alignment alignment, QGridLayout *layout, QWidget *tab, QString toolTip, bool setOpenLinks) {
    QLabel *Label = new QLabel(tab);
    Label->setText(label + " " + value);
    layout->addWidget(Label,row,col,alignment);
    Label->setToolTip(toolTip);
    Label->setOpenExternalLinks(setOpenLinks);
    Label->setObjectName(label);
}

void Populate::create_NewCareerBox(QGridLayout *layout, QWidget *tab) {
    NewCareerCheckBox = new QCheckBox(tab);
    NewCareerCheckBox->setObjectName("NewCareerCheckBox");
    NewCareerCheckBox->setText("New Career");
    layout->addWidget(NewCareerCheckBox, 18, 0, Qt::AlignLeft);

    QLabel *lblNewCareer = new QLabel(tab);
    lblNewCareer->setObjectName("lblNewCareer");
    lblNewCareer->setText("Career Name:");
    lblNewCareer->setDisabled(true);
    layout->addWidget(lblNewCareer, 18, 0, Qt::AlignRight);

    NewCareerLineEdit = new QLineEdit(tab);
    NewCareerLineEdit->setObjectName("NewCareerLineEdit");
    NewCareerLineEdit->setObjectName("NewCareerLineEdit");
    NewCareerLineEdit->setDisabled(true);
    layout->addWidget(NewCareerLineEdit, 18, 1, Qt::AlignCenter);
}

void Populate::create_radSH3DCEasy(QGridLayout *layout, QWidget *tab) {
    GrabData *grabDataObj = new GrabData();

    SH3DC_Type = new QButtonGroup(tab);
    radSH3DCEasy = new QRadioButton(tab);
    radSH3DCEasy->setObjectName("radSH3DCEasy");
    SH3DC_Type->addButton(radSH3DCEasy);
    radSH3DCEasy->setText("SH3 Dynamic Campaign EASY");
    layout->addWidget(radSH3DCEasy, 19, 0, Qt::AlignLeft);

    if((grabDataObj->return_line("radSH3DCEasy="))=="0") {
        radSH3DCEasy->setChecked(false);
    } else {
        radSH3DCEasy->setChecked(true);
    }
}

void Populate::create_radSH3DCOriginal(QGridLayout *layout, QWidget *tab) {
    GrabData *grabDataObj = new GrabData();

    radSH3DCOriginal = new QRadioButton(tab);
    radSH3DCOriginal->setObjectName("radSH3DCOriginal");
    SH3DC_Type->addButton(radSH3DCOriginal);
    radSH3DCOriginal->setText("SH3 Dynamic Campaign ORIGINAL");
    layout->addWidget(radSH3DCOriginal, 20, 0, Qt::AlignLeft);



    if((grabDataObj->return_line("radSH3DCOriginal="))=="1") {
        radSH3DCOriginal->setChecked(true);
    } else {
        radSH3DCOriginal->setChecked(false);
    }
}

void Populate::create_btnShowMarksFile(QGridLayout *layout, QWidget *tab) {
    btnShowMarksFile = new QPushButton(tab);
    btnShowMarksFile->setObjectName("btnShowMarksFile");
    btnShowMarksFile->setText("Show \"Marks.txt\" file");
    layout->addWidget(btnShowMarksFile,20, 1, Qt::AlignLeft);
    btnShowMarksFile->setStyleSheet("padding: 3px; padding-left: 5px; padding-right: 5px;");
    btnShowMarksFile->setToolTip("Click to see your \"Marks.txt\" file (used only when playing SH3DC Original).");
    btnShowMarksFile->setDisabled(true);
    btnShowMarksFile->setVisible(false);

    GrabData *grabDataObj = new GrabData();

    if((grabDataObj->return_line("radSH3DCOriginal="))=="1") {
        btnShowMarksFile->setDisabled(false);
        btnShowMarksFile->setVisible(true);
    }

}

void Populate::create_lblMarksExample(QGridLayout *layout, QWidget *tab) {
    lblMarksExample = new QLabel(tab);
    lblMarksExample->setObjectName("lblMarksExample");
    lblMarksExample->setText("<a href='file:///" + QDir::currentPath() +"/EXAMPLE OF Marks.txt'>Example of \"Marks.txt\"</a>");

    lblMarksExample->setOpenExternalLinks(true);

    layout->addWidget(lblMarksExample, 20, 2, Qt::AlignLeft);
    lblMarksExample->setToolTip("Click here to see an example of what the <br>\"Marks.txt\" file should look like.");
    lblMarksExample->setDisabled(true);
    lblMarksExample->setVisible(false);

    GrabData *grabDataObj = new GrabData();

    if((grabDataObj->return_line("radSH3DCOriginal="))=="1") {
        lblMarksExample->setDisabled(false);
        lblMarksExample->setVisible(true);
    }
}

void Populate::create_lblForgotMark(QGridLayout *layout, QWidget *tab) {
    lblForgotMark = new QLabel(tab);
    lblForgotMark->setObjectName("lblForgotMark");
    layout->addWidget(lblForgotMark, 20, 17, Qt::AlignLeft);
    lblForgotMark->setText("<a href='forgot'>Forgot to mark a sinking?</a>");
    lblForgotMark->setOpenExternalLinks(false);
    lblForgotMark->setToolTip("Click here if you forgot to save after a sinking, or <br>forgot to mark a sinking on the navigation map with the pencil.");
}

void Populate::create_patrolTabData(QGridLayout *Pat_layout, QWidget *patrol_Tab, QString career, int patrolNum, QFile *file){

    SavesData *savesDataObj = new SavesData();
;
    int numSunkSH3DC = numberSunk(file, "Patrol=" + QString::number(patrolNum));
    int numSunkNonSH3DC = numberSunk_nonSH3DC(career, QString::number(patrolNum), 0);


    if(numSunkSH3DC < numSunkNonSH3DC) {
        if (numSunkNonSH3DC > 1) {
            create_LabelPair("<b>Ships sunk:</b>", QString::number(numSunkSH3DC)+"  " + "<a href=\"http://google.com\">" + "<img src=\"://images/warning-icon.png\" width=\"15\" height=\"15\"\">" + "</a>" , 1, 0, Qt::AlignLeft, Pat_layout, patrol_Tab, "SH3DC has found " + QString::number(numSunkNonSH3DC) +" ships, but has processed "+ QString::number(numSunkSH3DC) + " of them in this patrol." +"\n It is recommended that you run the SH3DC scripts.", false);
        } else{
            create_LabelPair("<b>Ships sunk:</b>", QString::number(numSunkSH3DC)+"  " + "<a href=\"http://google.com\">" + "<img src=\"://images/warning-icon.png\" width=\"15\" height=\"15\"\">" + "</a>" , 1, 0, Qt::AlignLeft, Pat_layout, patrol_Tab, "SH3DC has found " + QString::number(numSunkNonSH3DC) +" ship, but has processed "+ QString::number(numSunkSH3DC) + " of them in this patrol." +"\n It is recommended that you run the SH3DC scripts.", false);
        }
    } else{
        create_LabelPair("<b>Ships sunk:</b>", QString::number(numberSunk(file, "Patrol=" + QString::number(patrolNum))), 1, 0, Qt::AlignLeft, Pat_layout, patrol_Tab, NULL, false);
    }
    create_LabelPair("<b>Start date:</b>", savesDataObj->patrol_StartDate(career, QString::number(patrolNum-1)), 1, 2, Qt::AlignLeft, Pat_layout, patrol_Tab, NULL, false);
    create_LabelPair("<b>End date:</b>", savesDataObj->patrol_EndDate(career, QString::number(patrolNum-1)), 1, 4, Qt::AlignLeft, Pat_layout, patrol_Tab, NULL, false);


    QString subType = "<a href='http://www.uboat.net/types/" + savesDataObj->subType(career, QString::number(patrolNum-1)).toLower() +".htm'>" + savesDataObj->subType(career, QString::number(patrolNum-1)) + "</a>";
    create_LabelPair("<b>Sub Type:</b>", subType , 1, 6, Qt::AlignLeft, Pat_layout, patrol_Tab, "Click to visit uboat.net's specifications of your uboat type.", true);

    QRegExp rx("\\-"); //RegEx for '-'
    QStringList query = (savesDataObj->subName(career, QString::number(patrolNum-1))).split(rx);
    QString subName = "<a href='http://www.uboat.net/boats/u" + query.value(1) +".htm'>" + savesDataObj->subName(career, QString::number(patrolNum-1)) + "</a>";
    create_LabelPair("<b>Sub Name:</b>", subName, 1, 8, Qt::AlignLeft, Pat_layout, patrol_Tab,"Click to visit uboat.net's history of your u-boat.", true);


    QRegExp rxex("\\/"); //RegEx for '/'
    QStringList query1 = (savesDataObj->flotilla(career, QString::number(patrolNum-1))).split(rxex);

    QRegExp rxex2("\\&"); //RegEx for '&'
    QStringList query2;
    QString flotilla;
    QStringList strList;

    for(int c=0;c < query1.size(); c++){
        query2 = ((query1.value(c).split(rxex2)));
        //qDebug() << "CONTENTS " << query2.value(0) << query2.value(1) << query2.value(2) << query2.value(3);

        for(int a=0; a < query2.size(); a++) {
            int b=33;

            while(!(query2.value(a).contains(QString::number(b)))){
                b--;
                if (b==0) {
                    break;
                }
            }

            if((query2.value(a).contains("Eisbär")) || (query2.value(a).contains("Seehund"))) {
                strList.append("<a href='http://www.uboat.net/ops/monsun2.htm#content'>" + query2.value(a) + "</a>");
            } else if((query2.value(a).contains("Monsun")) || (query2.value(a).contains("Monsoon"))) {
                strList.append("<a href='http://www.uboat.net/ops/monsun3.htm#content'>" + query2.value(a) + "</a>");
            } else{
                if(b==0) {
                    strList.append(query2.value(a));
                } else{
                    strList.append("<a href='http://www.uboat.net/flotillas/"+ QString::number(b) +"flo.htm'>" + query2.value(a) + "</a>");
                }

                if((a < query2.size()-1)) {
                    strList.append("&");
                }
            }

        }

        if((c < query1.size()-1)) {
            strList.append(" / ");
        }

    }

    for(int a=0; a < strList.size(); a++) {
        flotilla.append(strList.value(a));
    }
    create_LabelPair("<b>Flotilla:</b>", flotilla, 1, 10, Qt::AlignLeft, Pat_layout, patrol_Tab, "Click to visit uboat.net's history of your flotilla.", true);


}

void Populate::NewCareerLineEdit_disabled(bool value, QTabWidget* careersTW) {

    //QLineEdit *NewCareerLineEdit2 = careersTW->findChild<QLineEdit*>("NewCareerLineEdit");
    //QLabel *lblNewCareer = careersTW->findChild<QLabel*>("lblNewCareer");
    //NewCareerLineEdit2->setDisabled(value);
    //lblNewCareer->setDisabled(value);
    careersTW->findChild<QLineEdit*>("NewCareerLineEdit")->setDisabled(value);
    careersTW->findChild<QLabel*>("lblNewCareer")->setDisabled(value);
}

int Populate::numberSunk_nonSH3DC(QString career, QString patrol, int numOfPatrols) {
    GrabData *grabDataObj = new GrabData();
    int sunk = 0;
    if(patrol==NULL) {
        for(int i=0 ;i < numOfPatrols;i++) {
            QFile file(grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Log_"+ QString::number(i) + ".cfg");
            if(file.exists()){
                sunk += numberSunk(&file, "Ship sunk!");
            }
        }
    }
    else {
        QFile file(grabDataObj->return_sh3Saves() + "/data/cfg/Careers/" + career + "/Log_"+ QString::number(patrol.toInt()-1) + ".cfg");
        if(file.exists()){
            sunk += numberSunk(&file, "Ship sunk!");
        }
    }
    return sunk;
}

QPushButton* Populate::return_btnCareer(QWidget *parent) {

    return parent->findChild<QPushButton *>("btnCareer");
    //return btnCareer;
}

QPushButton* Populate::return_btnScriptsOnly(QWidget *parent) {

    return parent->findChild<QPushButton *>("btnScriptsOnly");

}

QPushButton* Populate::return_btnRefresh(QWidget *parent) {
    return parent->findChild<QPushButton *>("btnRefresh");
    //return btnRefresh;
}

QCheckBox* Populate::return_NewCareerCheckBox(QWidget *parent) {
    return parent->findChild<QCheckBox *>("NewCareerCheckBox");
    //return NewCareerCheckBox;
}
QLabel* Populate::return_lblNewCareer(QWidget *parent){
    return parent->findChild<QLabel *>("lblNewCareer");
}

QLineEdit* Populate::return_NewCareerLineEdit(QWidget *parent){
    return parent->findChild<QLineEdit *>("NewCareerLineEdit");
    //return NewCareerLineEdit;
}

QLineEdit* Populate::return_txtNewCareer(QWidget *parent){
    return parent->findChild<QLineEdit *>("txtNewCareer");
    //return txtNewCareer;
}

QWidget* Populate::return_CareersTW_Patrols(QWidget *parent){
    return parent->findChild<QWidget *>("CareersTW_Patrols");
    //return CareersTW_Patrols;
}

QTabWidget* Populate::returnTW_CareersTW_Patrols(QWidget *parent){
    return parent->findChild<QTabWidget *>("CareersTW_Patrols");
    //return CareersTW_Patrols;
}

QRadioButton* Populate::return_radSH3DCEasy(QWidget *parent){
    return parent->findChild<QRadioButton *>("radSH3DCEasy");
    //return radSH3DCEasy;
}

QRadioButton* Populate::return_radSH3DCOriginal(QWidget *parent){
    return parent->findChild<QRadioButton *>("radSH3DCOriginal");
    //return radSH3DCOriginal;
}

QRadioButton* Populate::return_radSH3DCEasy_NC(QWidget *parent){
    return parent->findChild<QRadioButton *>("radSH3DCEasy_NC");
    //return radSH3DCEasy_NC;
}

QRadioButton* Populate::return_radSH3DCOriginal_NC(QWidget *parent){
    return parent->findChild<QRadioButton *>("radSH3DCOriginal_NC");
    //return radSH3DCOriginal_NC;
}

QPushButton* Populate::return_btnShowMarksFile(QWidget *parent){
    return parent->findChild<QPushButton *>("btnShowMarksFile");
    //return btnShowMarksFile;
}

QLabel* Populate::return_lblMarksExample(QWidget *parent){
    return parent->findChild<QLabel *>("lblMarksExample");
    //return lblMarksExample;
}

QLabel* Populate::return_lblForgotMark(QWidget *parent) {
    return parent->findChild<QLabel *>("lblForgotMark");
    //return lblForgotMark;
}
/*
QString* Populate::return_subType(QWidget *parent){
    return subType;
}
*/
