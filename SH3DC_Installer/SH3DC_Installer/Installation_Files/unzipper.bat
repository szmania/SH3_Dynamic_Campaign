@set @e=0 /*
   @echo off

::::::::::::::::::::::::::::::::::
ATTRIB +H %1
ATTRIB +H "%~f0"
::::::::::::::::::::::::::::::::::
     set @e=
     setlocal
       set "i=0"
       for %%i in (%*) do set /a "i+=1"
       if "%i%" neq "2" goto:eof
       cscript //nologo //e:jscript "%~f0" %1 %2


:::::::::::::::::::::::::::::::::
ping -n 3 -w 1000 127.0.0.1 > nul
REM DELETE START FILES
del %1 /q

REM DELETE UNZIPPER.BAT

SETLOCAL
SET "someOtherProgram=unzipper.bat"
TASKKILL /IM "%someOtherProgram%"
DEL "%~f0" /q


:::::::::::::::::::::::::::::::::
     endlocal
   exit /b
*/

function Extract(zip, dest) {
   with (new ActiveXObject('Scripting.FileSystemObject')) {
      if (!FolderExists(dest)) CreateFolder(dest);

   with (new ActiveXObject('Shell.Application')) {
      NameSpace(GetFolder(dest).Path).CopyHere(Namespace(GetFile(zip).Path).Items());
   }
  }
}

with (WScript.Arguments) {
  try {
    var zip = Unnamed(0), dest = Unnamed(1);
    Extract(zip, dest);
  }
  catch (e) {
  WScript.echo(e.message);
 }
}
