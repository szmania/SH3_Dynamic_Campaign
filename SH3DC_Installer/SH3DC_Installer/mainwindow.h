#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "waitdialog.h"

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QAbstractItemModel>
#include <QFileDialog>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
    void treeWidget(QTreeWidgetItem* fullPack, QTreeWidgetItem* sh3dc_FullPack,
                    QTreeWidgetItem* captainsJournal_FullPack, QTreeWidgetItem* sh3dc, QTreeWidgetItem* captainsJournal);
    void checkIfExists(QString* sh3Dir, QString* profiles, QString* sh3Cmdr);
    void launchBat(QString*);
    void outputPaths(QString* SH3ProgramFilesPath, QString* userProfilePath, QString* SH3CommanderPath);
    void unzip();
    void delTempFiles();



signals:
    void itemChanged(QTreeWidgetItem*, int*);

private slots:

    void on_pushButton_Next_clicked();

    void on_pushButton_Prev_clicked();

    void on_radioButton_Disagree_clicked();

    void on_radioButton_Agree_clicked();

    void on_checkBox_clicked(bool checked);

    void on_pushButton_Exit_clicked();

    void updateChecks(QTreeWidgetItem*, int);

    void on_pushButton_DirSaves_clicked();

    void on_pushButton_DirSH3_clicked();

    void on_pushButton_DirSH3Cmdr_clicked();

    void installation_directory_page();

    void close_Mainwindow();

private:
    Ui::MainWindow *ui;
    int page;

    QTreeWidgetItem* sh3dcFullPack;
    QTreeWidgetItem* fullPack;
    QTreeWidgetItem* captainsJournal_FullPack;
    QTreeWidgetItem* sh3dc;
    QTreeWidgetItem* captainsJournal;

    QString programFilesPath;
    QString SH3ProgramFilesPath;
    QString fullSH3ProgramFilesPath;
    QString userProfilePath;
    QString fullUserProfilePath;
    QString SH3CommanderPath;
    QString fullSH3CommanderPath;
    QString batPath;

    QString filepath;
    QFileDialog dialog;
    WaitDialog *wDialog;

};

#endif // MAINWINDOW_H
