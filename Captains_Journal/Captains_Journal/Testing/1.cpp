#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;



int main() {
    //HWND hwnd = FindWindow(NULL,TEXT("SilentHunter3 - 1024 x 720"));
    HWND hwnd2 = FindWindow("3D-Engine", 0);
    if(hwnd2) {
        cout << "Found \n";
    }
    else {
        cout << "not found \n";
    }
    //cout << hwnd << "\n";
    cout << hwnd2;
    ofstream myfile;
    myfile.open ("hwnd.txt");
    myfile << hwnd2;
    myfile.close();


}
