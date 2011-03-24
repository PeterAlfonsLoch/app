@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by VMSSYNCHEDITOR.HPJ. >"hlp\vmssyncheditor.hm"
echo. >>"hlp\vmssyncheditor.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\vmssyncheditor.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\vmssyncheditor.hm"
echo. >>"hlp\vmssyncheditor.hm"
echo // Prompts (IDP_*) >>"hlp\vmssyncheditor.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\vmssyncheditor.hm"
echo. >>"hlp\vmssyncheditor.hm"
echo // Resources (IDR_*) >>"hlp\vmssyncheditor.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\vmssyncheditor.hm"
echo. >>"hlp\vmssyncheditor.hm"
echo // Dialogs (IDD_*) >>"hlp\vmssyncheditor.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\vmssyncheditor.hm"
echo. >>"hlp\vmssyncheditor.hm"
echo // Frame Controls (IDW_*) >>"hlp\vmssyncheditor.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\vmssyncheditor.hm"
REM -- Make help for Project VMSSYNCHEDITOR


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\vmssyncheditor.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\vmssyncheditor.hlp" goto :Error
if not exist "hlp\vmssyncheditor.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\vmssyncheditor.hlp" Debug
if exist Debug\nul copy "hlp\vmssyncheditor.cnt" Debug
if exist Release\nul copy "hlp\vmssyncheditor.hlp" Release
if exist Release\nul copy "hlp\vmssyncheditor.cnt" Release
echo.
goto :done

:Error
echo hlp\vmssyncheditor.hpj(1) : error: Problem encountered creating help file

:done
echo.
