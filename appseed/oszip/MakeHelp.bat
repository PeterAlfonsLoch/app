@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by OSZIP.HPJ. >"hlp\oszip.hm"
echo. >>"hlp\oszip.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\oszip.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\oszip.hm"
echo. >>"hlp\oszip.hm"
echo // Prompts (IDP_*) >>"hlp\oszip.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\oszip.hm"
echo. >>"hlp\oszip.hm"
echo // Resources (IDR_*) >>"hlp\oszip.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\oszip.hm"
echo. >>"hlp\oszip.hm"
echo // Dialogs (IDD_*) >>"hlp\oszip.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\oszip.hm"
echo. >>"hlp\oszip.hm"
echo // Frame Controls (IDW_*) >>"hlp\oszip.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\oszip.hm"
REM -- Make help for Project OSZIP


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\oszip.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\oszip.hlp" goto :Error
if not exist "hlp\oszip.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\oszip.hlp" Debug
if exist Debug\nul copy "hlp\oszip.cnt" Debug
if exist Release\nul copy "hlp\oszip.hlp" Release
if exist Release\nul copy "hlp\oszip.cnt" Release
echo.
goto :done

:Error
echo hlp\oszip.hpj(1) : error: Problem encountered creating help file

:done
echo.
