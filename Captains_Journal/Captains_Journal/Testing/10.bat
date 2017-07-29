@echo off

del hwnd.txt
ping -n 7 -w 1000 127.0.0.1 > nul

start 1.exe
ping -n 2 -w 1000 127.0.0.1 > nul
start Captains_Journal.exe