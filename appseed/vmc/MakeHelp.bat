@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by VMC.HPJ. >"hlp\vmc.hm"
echo. >>"hlp\vmc.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\vmc.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\vmc.hm"
echo. >>"hlp\vmc.hm"
echo // Prompts (IDP_*) >>"hlp\vmc.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\vmc.hm"
echo. >>"hlp\vmc.hm"
echo // Resources (IDR_*) >>"hlp\vmc.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\vmc.hm"
echo. >>"hlp\vmc.hm"
echo // Dialogs (IDD_*) >>"hlp\vmc.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\vmc.hm"
echo. >>"hlp\vmc.hm"
echo // Frame Controls (IDW_*) >>"hlp\vmc.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\vmc.hm"
REM -- Make help for Project VMC


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\vmc.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\vmc.hlp" goto :Error
if not exist "hlp\vmc.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\vmc.hlp" Debug
if exist Debug\nul copy "hlp\vmc.cnt" Debug
if exist Release\nul copy "hlp\vmc.hlp" Release
if exist Release\nul copy "hlp\vmc.cnt" Release
echo.
goto :done

:Error
echo hlp\vmc.hpj(1) : error: Problem encountered creating help file

:done
echo.
