#ifndef MEMORY_H
#define MEMORY_H

#include <QObject>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <TlHelp32.h>
#include <iostream>
#include <sstream>
#include <string>
#include <QDebug>
#include <Psapi.h>
#include <TlHelp32.h>
#define PSAPI_VERSION 1
#include <tchar.h>
#include <psapi.h>

//#include "stdafx.h"
//#pragma comment( lib, "psapi" )

using namespace std;

class Memory : public QObject
{
    Q_OBJECT

protected:
    DWORD processID;
    HANDLE processHandle;
    DWORD baseAddress;


    void findSH3ExecutableSize();

public:
    bool moddedEXE;

    explicit Memory(QObject *parent = 0);
    bool sh3IsRunning();
    void getSh3ProcessInfo();
    QString readMemory_qString(QList<DWORD>, int);
    float readMemory_float(QList<DWORD>);
    double readMemory_double(QList<DWORD>);
    ULONG getModuleBase(wchar_t *ModuleName, ULONG ProcessId);
    HANDLE getProcessByName(QString);
    QString getCareerName();



signals:

public slots:

};

#endif // MEMMANAGEMENT_H
