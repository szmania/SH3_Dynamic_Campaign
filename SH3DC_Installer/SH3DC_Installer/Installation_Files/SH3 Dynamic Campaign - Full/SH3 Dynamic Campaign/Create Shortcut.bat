
@echo off

SETLOCAL ENABLEDELAYEDEXPANSION

cd %~dp0

mkdir "%ALLUSERSPROFILE%\Start Menu\Programs\SH3 Dynamic Campaign"
 

for /f "usebackq tokens=1* delims==" %%q in ("Dynamic Campaign\DATA\settings.txt") do (
	set line=%%q
	set sh3directory=%%r
	if "!line!"=="sh3Directory" goto next
	
)
:next

set SCRIPT="%TEMP%\%RANDOM%-%RANDOM%-%RANDOM%-%RANDOM%.vbs"

echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%ALLUSERSPROFILE%\Start Menu\Programs\SH3 Dynamic Campaign\SH3 Dynamic Campaign.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "!sh3directory!\SH3 Dynamic Campaign\Dynamic Campaign\SH3DC.exe" >> %SCRIPT%
echo oLink.WorkingDirectory = "!sh3directory!\SH3 Dynamic Campaign\Dynamic Campaign" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%

cscript /nologo %SCRIPT%
del %SCRIPT%
