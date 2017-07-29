#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QIODevice>
#include <QMessageBox>
#include <QTextStream>
#include <QWindow>
#include <QProcess>
#include <QPixmap>
#include <QDesktopWidget>
#include <QPoint>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    //Sh3Window = QWindow::fromWinId(hwnd);

    Sh3Window = QWindow::fromWinId(getHWND());
    Sh3Window->setWindowState(Qt::WindowMinimized);
    //Sh3Window->setFlags(Qt::Dialog);
    //Sh3Window->setFlags(Qt::Window);
    //Sh3Window->setGeometry(50,100,924,650);
    //Sh3Window->setVisibility(QWindow::Windowed);


    //Sh3Window->setWindowState(Qt::WindowFullScreen);
    //Sh3Window->setWindowState(Qt::WindowNoState);
    //ui->widget->createWindowContainer(Sh3Window,this,Qt::Dialog);

    loadFile();

    grabDate();



}

MainWindow::~MainWindow()
{
    //Sh3Window->setWindowState(Qt::WindowMaximized);
    Sh3Window->setWindowState(Qt::WindowFullScreen);
    Sh3Window->setWindowState(Qt::WindowActive);
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    mFilename = "";
    ui->textEdit->setPlainText("");
}

void MainWindow::on_actionOpen_triggered()
{
    //Open dialog with filepath and filename filters.
    QString file = dialog.getOpenFileName(this,tr("Open a file"), filepath, tr("SH3 Log files (*.clg *.cfg *.txt)"));

    if(!file.isEmpty())
    {
        QFile sFile(file); 
        if(sFile.open(QFile::ReadOnly | QFile::Text))
        {
            mFilename = file;
            QTextStream in(&sFile);
            QString text = in.readAll();
            sFile.close();

            ui->textEdit->setPlainText(text);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{

    //Test for filename
    QFile sFile(filepath);
    if(sFile.open(QFile::WriteOnly |  QFile::Text))
    {
        QTextStream out(&sFile);

        out << ui->textEdit->toPlainText();

        sFile.flush();
        sFile.close();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    //Save As dialog with filepath only.
    QString file = QFileDialog::getSaveFileName(this,("Save file as"), filepath);

    if(!file.isEmpty())
    {
        mFilename = file;
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::loadFile(){

    // QFile file("/text.txt"); //If present in Resource
    QFile file("C:/Documents and Settings/Shirin/My Documents/Dropbox/SH3 Files/Captains Journal/Captains_Journal/Text Files/text.txt"); //If present on system
    //QFile file("E:/Dropbox/SH3 Files/Captains Journal/Captains_Journal/Text Files/text.txt"); //If present on system

    //Grabbing filename
    QFileInfo fn(file);
    mFilename = fn.fileName();

    //Grabbing filepath
    QFileInfo fp(file);
    filepath = fp.filePath();

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,"Captain's Journal Error", "Captain's Journal not found!");
        return;
    }

    QTextStream stream(&file);
    QString line = stream.readAll();
    file.flush();
    file.close();
    ui->textEdit->setText(line);


  }

void MainWindow::grabDate(){
    ui->lblDateChange->setText("August 5, 1940");
}



WId MainWindow::getHWND(){
    QFile file("hwnd.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);
    QString line;
    while(!in.atEnd()) {
        line = in.readLine();
    }
    file.close();
    WId hwnd = line.toUInt(0,16);
    return hwnd;

}



void MainWindow::on_pushButton_clicked()
{
    /*------ Take a screenshot of a window ------*/
    QPixmap qPixMap = QPixmap::grabWidget(Sh3Window);

    ui->label_2->setPixmap(qPixMap.scaledToHeight(70));
    //ui->label_2->setText(QxtWindowSystem::findWindow"SilentHunter3 1024 x 768");
}

