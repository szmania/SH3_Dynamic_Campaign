#include "memory.h"
#include "grabdata.h"

#include <windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include <QDebug>
#include <Psapi.h>
#include <TlHelp32.h>
#define PSAPI_VERSION 1
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#include <QFile>
#include <QFileInfo>

//#include "stdafx.h"
//#pragma comment( lib, "psapi" )


using namespace std;

Memory::Memory(QObject *parent) :
    QObject(parent)
{
    this->findSH3ExecutableSize();
    this->getSh3ProcessInfo();

}


void Memory::findSH3ExecutableSize(){
    GrabData *grabDataObj = new GrabData();

    QFile sh3EXE(grabDataObj->sh3Directory + "/sh3.exe");
    QFileInfo sh3EXEFileInfo(sh3EXE);
    double megaBytes = sh3EXEFileInfo.size() / 1000.0 /1000.0;

    if (megaBytes > 2.0) {
        moddedEXE = false;

    }else{
        moddedEXE = true;
    }
//    qDebug() << megaBytes;
}

bool Memory::sh3IsRunning(){
    qDebug() << "Checking if Silent Hunter III is running.";
    HANDLE phandle = this->getProcessByName("sh3.exe");
    if (phandle){
        qDebug() << "Silent Hunter III is running.";
        return true;
    } else{
        qDebug() << "Silent Hunter III is NOT running.";
        return false;

    }
}

void Memory::getSh3ProcessInfo(){
//    DWORD pid;
//    HWND hwnd = FindWindow(NULL,L"SilentHunter3 - 1024 x 768"); //Finds the Window called "Minesweeper"
//    if(!hwnd) {
//        qDebug() <<"Window not found!\n";
//    }

//    GetWindowThreadProcessId(hwnd,&pid); //Get the process id and place it in pid
//    this->processID = pid;

    HANDLE phandle = this->getProcessByName("sh3.exe");

//    HANDLE phandle = OpenProcess(PROCESS_VM_READ,0,pid); //Get permission to read
    this->processHandle = phandle;
    if(!phandle) //Once again, if it fails, tell us
    {
        qDebug() <<"Could not get handle!\n";
    }
    ULONG pID = this->processID;
    ULONG EXEModuleBase = getModuleBase(0, pID);
    this->baseAddress = EXEModuleBase;

}

QString Memory::readMemory_qString(QList<DWORD> addressList, int charArraySize = 15){
    DWORD pointed;
    ULONG address;
    DWORD offset;
    char returned[50] = {0};
    charArraySize;

    for (int i = 0; i < addressList.count(); i++) {
        offset = addressList[i];

        if( i == 0){
            address = this->baseAddress  + offset;
        }else{
            address = pointed + offset;
        }

        if (i != addressList.count() - 1){
            ReadProcessMemory(this->processHandle,(LPVOID)(address),&pointed,sizeof(pointed),0);
        }else{
            ReadProcessMemory(this->processHandle,(LPVOID)(address),&returned,sizeof(returned),0);
        }
    }

   qDebug() << returned;
   qDebug() << "";
//    qDebug() << "Memory value returned:" << QString::fromStdString(returned);

    QString returned_str(returned);
    return returned_str;
}


float Memory::readMemory_float(QList<DWORD> addressList){
    DWORD pointed;
    ULONG address;
    DWORD offset;
    float returned;

    for (int i = 0; i < addressList.count(); i++) {
        offset = addressList[i];

        if( i == 0){
            address = this->baseAddress  + offset;
        }else{
            address = pointed + offset;
        }

        if (i != addressList.count() - 1){
            ReadProcessMemory(this->processHandle,(LPVOID)(address),&pointed,sizeof(pointed),0);
        }else{
            ReadProcessMemory(this->processHandle,(LPVOID)(address),&returned,sizeof(returned),0);
        }

    }
    qDebug() << "Memory value returned:" << returned;

    return returned;
}



double Memory::readMemory_double(QList<DWORD> addressList){
    DWORD pointed;
    ULONG address;
    DWORD offset;
    double returned;

    for (int i = 0; i < addressList.count(); i++) {

        offset = addressList[i];

        if( i == 0){
            address = this->baseAddress  + offset;

        }else{

            address = pointed + offset;
        }

        if (i != addressList.count() - 1){
            ReadProcessMemory(this->processHandle,(LPVOID)(address),&pointed,sizeof(pointed),0);

        }else{
            ReadProcessMemory(this->processHandle,(LPVOID)(address),&returned,sizeof(returned),0);
        }

    }
    qDebug() << "Memory value returned:" << returned;

    return returned;


}


ULONG Memory::getModuleBase(wchar_t *ModuleName, ULONG ProcessId)
{
   MODULEENTRY32W *me = new MODULEENTRY32W;

   HANDLE Snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessId);

   me->dwSize = sizeof(MODULEENTRY32W);
   if(Snap == INVALID_HANDLE_VALUE)
   {
      delete me;
      return 0;
   }

   BOOL bModule = Module32First(Snap, me);
   while(bModule)
   {
      if(!ModuleName|| _wcsicmp(me->szModule, ModuleName) == 0)
      {
         CloseHandle(Snap);
         return (ULONG)me->modBaseAddr;
      }

      bModule = Module32Next(Snap, me);
   }

   CloseHandle(Snap);
   delete me;
   return 0;
}


HANDLE Memory::getProcessByName(QString name)
{
    DWORD pid = 0;

    // Create toolhelp snapshot.
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 process;
    ZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);

    // Walkthrough all processes.
    if (Process32First(snapshot, &process))
    {
        do
        {
            wstring ws(process.szExeFile);
            string processName_str(ws.begin(), ws.end());
            QString processName =  QString::fromStdString(processName_str);
            if (processName.contains(name)){
                qDebug() << "Process name found: " << processName;
                pid = process.th32ProcessID;

                break;
            }

            // Compare process.szExeFile based on format of name, i.e., trim file path
            // trim .exe if necessary, etc.


        } while (Process32Next(snapshot, &process));
    }

    CloseHandle(snapshot);

    if (pid != 0)
    {
        this->processID = pid;
        return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    }
    return NULL;
}

QString Memory::getCareerName(){
    QList<DWORD> addressList;
//    addressList.append(0x5F5F60);

    addressList.append(0x1F5F60);
    QString careerName = this->readMemory_qString(addressList, 25);
//    QList<DWORD> addressList2;
//    addressList2.append(0x00154698);
//    addressList2.append(0x68);
//    float value2 = this->readMemory_float(addressList2);
//    qDebug() << value;
    return careerName;
}
