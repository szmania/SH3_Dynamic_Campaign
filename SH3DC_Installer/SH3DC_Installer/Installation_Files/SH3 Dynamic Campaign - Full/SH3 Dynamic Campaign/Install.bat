
@echo off

SETLOCAL ENABLEDELAYEDEXPANSION

echo Installing SH3 Dynamic Campaign...

for /f "usebackq tokens=1* delims==" %%q in ("Dynamic Campaign\DATA\settings.txt") do (
	set line=%%q
	set sh3directory=%%r
	if "!line!"=="sh3Directory" goto next
	
)
:next
for /f "usebackq tokens=1* delims==" %%r in ("Dynamic Campaign\DATA\settings.txt") do (
	set line=%%r
	set sh3saves=%%s
	if "!line!"=="sh3Saves" goto next2
)
:next2

for /f "usebackq tokens=1* delims==" %%s in ("Dynamic Campaign\DATA\settings.txt") do (
	set line=%%s
	set sh3commander=%%t
	if "!line!"=="sh3Commander" goto next3
)
:next3

mkdir "!sh3directory!\SH3 Dynamic Campaign\SH3DC-BACKUP\SH3 Dynamic Campaign"

copy /y Install.bat "!sh3directory!\SH3 Dynamic Campaign\SH3DC-BACKUP"

copy /y "Create Shortcut.bat" "!sh3directory!\SH3 Dynamic Campaign\SH3DC-BACKUP"

xcopy "Dynamic Campaign" "!sh3directory!\SH3 Dynamic Campaign\SH3DC-BACKUP\SH3 Dynamic Campaign" /e /y



SETLOCAL ENABLEDELAYEDEXPANSION



mkdir "!sh3directory!\SH3 Dynamic Campaign\Dynamic Campaign"

xcopy "Dynamic Campaign" "!sh3directory!\SH3 Dynamic Campaign\Dynamic Campaign" /e /y



if exist "!sh3saves!\data\cfg\Careers" (

	for /f "delims=" %%A in ('dir /A:D /b "!sh3saves!\data\cfg\Careers"') do ( 
		set careerdirectory=%%A

		if not exist "!sh3directory!\SH3 Dynamic Campaign\Dynamic Campaign\Careers\!careerdirectory!\Campaign_SCR.mis" (

		mkdir "!sh3directory!\SH3 Dynamic Campaign\Dynamic Campaign\Careers"

		mkdir "!sh3directory!\SH3 Dynamic Campaign\Dynamic Campaign\Careers\!careerdirectory!"

		copy /y "!sh3directory!\data\Campaigns\Campaign\Campaign_SCR.mis" "!sh3directory!\SH3 Dynamic Campaign\Dynamic Campaign\Careers\!careerdirectory!\Campaign_SCR.mis"
		copy /y "!sh3directory!\data\Campaigns\Campaign\Campaign_RND.mis" "!sh3directory!\SH3 Dynamic Campaign\Dynamic Campaign\Careers\!careerdirectory!\Campaign_RND.mis"
		)
	)
)

Exit