:: ******************************************
:: *
:: * Copyright 2011 ROCHA, Rodrigo C. O.
:: *
:: ******************************************
@echo off
echo Enter the name of the oberon file (without the file extension .obe):
set /p Input=

if not exist "%Input%.obe" (goto COMPILE_ERROR)

:COMPILE
oberonc "%Input%.obe" -x86
if not exist "%Input%.s" (goto ASSEMBLY_ERROR)

:ASSEMBLE
gas\as.exe -o "%Input%.o" "%Input%.s"
if not exist "%Input%.o" (goto ASSEMBLE_ERROR)

:LINK
gas\ld.exe -o "%Input%.exe" "gas/crt2.o" "gas/crtbegin.o" "gas/crtend.o" "%Input%.o" -L"gas/lib" -lmingw32 -lgcc -lmsvcrt -lkernel32
if not exist "%Input%.exe" (goto LINK_ERROR)

:DELETE
del /q "%Input%.o"
goto END

:COMPILE_ERROR
ECHO File "%Input%.obe" was not found
goto END

:ASSEMBLY_ERROR
ECHO It was not possible to create the file "%Input%.s"
goto END

:ASSEMBLE_ERROR
ECHO It was not possible to create the file "%Input%.o"
goto END

:LINK_ERROR
ECHO It was not possible to create the file "%Input%.exe"
goto END

:END
pause