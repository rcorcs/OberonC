:: ******************************************
:: *
:: * Copyright 2011 ROCHA, Rodrigo C. O.
:: *
:: ******************************************

@echo off
echo Executable File Name (without the extension file .exe):
set /p Input=

if not exist "%Input%.exe" (goto EXE_ERROR)

:RUN
%Input%
goto END

:EXE_ERROR
ECHO File "%Input%.exe" was not found
goto END

:END
pause