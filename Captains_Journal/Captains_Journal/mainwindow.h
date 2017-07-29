#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QIODevice>
#include <QWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();





    
private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionSave_As_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_pushButton_clicked();


protected:

    void grabDate();
    void loadFile();
    WId getHWND();

    QString mFilename;
    QString filepath;
    QFileDialog dialog;



private:
    Ui::MainWindow *ui;
    QWindow* Sh3Window;



};
#endif // MAINWINDOW_H
