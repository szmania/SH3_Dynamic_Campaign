/*
 * SH3 Dynamic Campaign
 * By Curtis Szmania (Machiavelli)
 * 9/9/2014
 *
*/

#include "mainwindow.h"


#include <QApplication>
#include <QTranslator>
#include <QtDebug>


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{

    QFile logFile("SH3DC.log");
    logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream sh3dcLogger(&logFile);

    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        sh3dcLogger << "Debug: " << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")\n";
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        sh3dcLogger << "Warning: " << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")\n";
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        sh3dcLogger << "Critical: " << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")\n";
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        sh3dcLogger << "Fatal: " << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")\n";
        abort();
    }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(myMessageOutput);
    //QTranslator translator;
    //translator.load("SH3DC_de_COMP.qm", ".");
    //a.installTranslator(&translator);

    MainWindow w;





    w.show();

    return a.exec();
}
