#-------------------------------------------------
#
# Project created by QtCreator 2013-12-28T13:44:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SH3DC_Installer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    waitdialog.cpp

HEADERS  += mainwindow.h \
    waitdialog.h

FORMS    += mainwindow.ui \
    waitdialog.ui

RESOURCES += \
    Images.qrc \
    Installation_Files.qrc

CONFIG += static

RC_FILE = icon.rc

