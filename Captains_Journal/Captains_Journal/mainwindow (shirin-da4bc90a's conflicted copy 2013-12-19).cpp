#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "getinfo.h"


#include <QFileDialog>
#include <QIODevice>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    loadFile();

}

MainWindow::~MainWindow()
{
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

    // QFile file(":/text.txt"); //If present in Resource

    QFile file("C:/Documents and Settings/Shirin/My Documents/Dropbox/SH3 Files/Captains Journal/Captains_Journal/Text Files/text.txt"); //If present on system

    //Grabbing filename
    QFileInfo fn(file);
    mFilename = fn.fileName();

    //Grabbing filepath
    QFileInfo fp(file);
    filepath = fp.filePath();

    file.open(QIODevice::ReadOnly);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open current Captain's Journal!";
        return;
    }
    QTextStream stream(&file);
    QString line = stream.readAll();
    file.close();
    ui->textEdit->setText(line);

    grabDate();

  }

void MainWindow::grabDate(){

    ui->lblDateChange->setText("August 5, 1940");

}





