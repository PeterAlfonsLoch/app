@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by VMSAUDIOPROFILE.HPJ. >"hlp\vmsaudioprofile.hm"
echo. >>"hlp\vmsaudioprofile.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\vmsaudioprofile.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\vmsaudioprofile.hm"
echo. >>"hlp\vmsaudioprofile.hm"
echo // Prompts (IDP_*) >>"hlp\vmsaudioprofile.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\vmsaudioprofile.hm"
echo. >>"hlp\vmsaudioprofile.hm"
echo // Resources (IDR_*) >>"hlp\vmsaudioprofile.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\vmsaudioprofile.hm"
echo. >>"hlp\vmsaudioprofile.hm"
echo // Dialogs (IDD_*) >>"hlp\vmsaudioprofile.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\vmsaudioprofile.hm"
echo. >>"hlp\vmsaudioprofile.hm"
echo // Frame Controls (IDW_*) >>"hlp\vmsaudioprofile.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\vmsaudioprofile.hm"
REM -- Make help for Project VMSAUDIOPROFILE


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\vmsaudioprofile.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\vmsaudioprofile.hlp" goto :Error
if not exist "hlp\vmsaudioprofile.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\vmsaudioprofile.hlp" Debug
if exist Debug\nul copy "hlp\vmsaudioprofile.cnt" Debug
if exist Release\nul copy "hlp\vmsaudioprofile.hlp" Release
if exist Release\nul copy "hlp\vmsaudioprofile.cnt" Release
echo.
goto :done

:Error
echo hlp\vmsaudioprofile.hpj(1) : error: Problem encountered creating help file

:done
echo.
