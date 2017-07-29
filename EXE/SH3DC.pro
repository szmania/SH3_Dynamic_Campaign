#-------------------------------------------------
#
# Project created by QtCreator 2014-06-20T12:25:34
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SH3DC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    populate.cpp \
    batch.cpp \
    table.cpp \
    grabdata.cpp \
    savesdata.cpp \
    aboutdialog.cpp \
    forgotdialog.cpp \
    settingsdialog.cpp \
    backupdialog.cpp \
    crashdialog.cpp \
    uninstalldialog.cpp \
    externalprograms.cpp \
    sh3dc_startup.cpp \
    memory.cpp \
    campaign.cpp \
    sh3monitorthread.cpp \
    sh3processing.cpp

HEADERS  += mainwindow.h \
    populate.h \
    batch.h \
    table.h \
    grabdata.h \
    savesdata.h \
    aboutdialog.h \
    forgotdialog.h \
    settingsdialog.h \
    backupdialog.h \
    crashdialog.h \
    uninstalldialog.h \
    externalprograms.h \
    sh3dc_startup.h \
    memory.h \
    campaign.h \
    sh3monitorthread.h \
    sh3processing.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    forgotdialog.ui \
    settingsdialog.ui \
    backupdialog.ui \
    crashdialog.ui \
    uninstalldialog.ui

RESOURCES += \
    images.qrc

RC_FILE = icon.rc

TRANSLATIONS = SH3DC_de_COMP.ts

CONFIG += import_plugins
