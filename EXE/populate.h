#ifndef POPULATE_H
#define POPULATE_H



#include "batch.h"
#include "table.h"
#include "savesdata.h"
#include "grabdata.h"


#include <QWidget>
#include <QFile>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>
#include <QButtonGroup>
#include <QMessageBox>


class Populate: public QObject
{
    Q_OBJECT

signals:

public:
    Populate(QObject *parent = 0);
    ~Populate();
    void careerTab(QWidget*, QString);
    void newCareerTab(QWidget*);
    void create_CareersTW_Patrols(QWidget*, QGridLayout*, int, QString);
    void create_btnCareer(QWidget*, QGridLayout*);
    void create_btnScriptsOnly(QWidget*, QGridLayout*);
    void create_btnRefresh(QWidget*, QGridLayout*);
    void create_LabelPair(QString, QString, int, int, Qt::Alignment, QGridLayout*, QWidget*, QString, bool);
    void create_NewCareerBox(QGridLayout*, QWidget*);
    void create_radSH3DCEasy(QGridLayout*, QWidget*);
    void create_radSH3DCOriginal(QGridLayout*, QWidget*);
    void create_btnShowMarksFile(QGridLayout*, QWidget*);
    void create_lblMarksExample(QGridLayout*, QWidget*);
    void create_patrolTabData(QGridLayout*, QWidget*, QString, int, QFile*);
    void create_lblForgotMark(QGridLayout*, QWidget*);


    void sunkData(QString, QWidget*, QGridLayout*, int);
    int numberSunk(QFile*, QString);
    void NewCareerLineEdit_disabled(bool, QTabWidget*);
    int numberSunk_nonSH3DC(QString, QString, int);

    QPushButton* return_btnCareer(QWidget *);
    QPushButton* return_btnScriptsOnly(QWidget *);
    QPushButton* return_btnRefresh(QWidget *);
    QCheckBox* return_NewCareerCheckBox(QWidget *);
    QLabel* return_lblNewCareer(QWidget *);
    QLineEdit* return_NewCareerLineEdit(QWidget *);
    QLineEdit* return_txtNewCareer(QWidget *);
    QWidget* return_CareersTW_Patrols(QWidget *);
    QTabWidget* returnTW_CareersTW_Patrols(QWidget *);
    //QGridLayout* return_layout(QWidget *);
    QRadioButton* return_radSH3DCEasy(QWidget *);
    QRadioButton* return_radSH3DCOriginal(QWidget *);
    QRadioButton* return_radSH3DCEasy_NC(QWidget *);
    QRadioButton* return_radSH3DCOriginal_NC(QWidget *);
    QPushButton* return_btnShowMarksFile(QWidget *);
    QLabel* return_lblMarksExample(QWidget *);
    QLabel* return_lblForgotMark(QWidget *);
    //QString* return_subType(QWidget *);


private:


    QPushButton *btnCareer;
    QPushButton *btnScriptsOnly;
    QPushButton *btnRefresh;
    QCheckBox *NewCareerCheckBox;
    QLineEdit *NewCareerLineEdit;
    QLineEdit *txtNewCareer;
    QTabWidget *CareersTW_Patrols;
    QWidget *patrol_Tab;
    QButtonGroup *SH3DC_Type;
    QRadioButton *radSH3DCEasy = NULL;
    QRadioButton *radSH3DCOriginal = NULL;
    //QButtonGroup *SH3DC_Type_NC = NULL;
    QRadioButton *radSH3DCEasy_NC = NULL;
    QRadioButton *radSH3DCOriginal_NC = NULL;
    QPushButton *btnShowMarksFile;
    QLabel *lblMarksExample;
    QLabel *lblForgotMark;
    //QString *subType;


};

#endif // POPULATE_H
