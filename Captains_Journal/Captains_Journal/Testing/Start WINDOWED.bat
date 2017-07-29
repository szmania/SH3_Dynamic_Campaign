@echo off

setlocal enabledelayedexpansion

del hwnd.txt

set "sh3saves=C:\Users\P Ditty\Documents\SH3"
set "dSource2=!sh3saves!\data\cfg\Careers"
set fType2=*.clg


set currentDateTime=%DATE:~-4%%DATE:~7,2%%DATE:~4,2%%TIME:~0,2%%TIME:~3,2%


ping -n 10 -w 1000 127.0.0.1 > nul
setlocal enabledelayedexpansion
:loop

for /f "delims=" %%f in ('dir /a-d /b /s "!dSource2!\!fType2!"') do (
	set fullpath3=%%f
	for /D %%I in ("!fullpath3!") do set name=%%~nI
	echo !name! | findstr /I /C:"journal"
	if not errorlevel 1 (
		for /D %%F in ("!fullpath3!") do set search=%%~tF
		CALL :CHECK2	
	)
)


ping -n 10 -w 1000 127.0.0.1 > nul

goto loop


:CHECK2
if "%search:~17,2%" EQU "PM" (
	if "%search:~11,2%" NEQ "12" (
		set /a "hours=%search:~11,2%+12"
		set comps=%search:~6,4%%search:~3,2%%search:~0,2%!hours!%search:~14,2%
	) else (
		set comps=%search:~6,4%%search:~3,2%%search:~0,2%%search:~11,2%%search:~14,2%
	)
) else (
	set comps=%search:~6,4%%search:~3,2%%search:~0,2%%search:~11,2%%search:~14,2%
)

echo !search!
echo !oldDate!
echo !comps!
echo !currentDateTime!


if "!search!" NEQ "!oldDate!" (
	if "!comps!" GEQ "!currentDateTime!" (
		ECHO FOUND
		tasklist /FI "IMAGENAME eq Captains_Journal.exe" | find /i "Captains_Journal.exe"  
		IF NOT ERRORLEVEL 1 GOTO :EOF
		echo Starting Capatains_Journal.exe	
		start 1.exe
		ping -n 2 -w 1000 127.0.0.1 > nul
		start Captains_Journal.exe
		set oldDate=!search!
	)
)
GOTO :EOF

