@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by MK1EXPANDER.HPJ. >"hlp\mk1expander.hm"
echo. >>"hlp\mk1expander.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\mk1expander.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\mk1expander.hm"
echo. >>"hlp\mk1expander.hm"
echo // Prompts (IDP_*) >>"hlp\mk1expander.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\mk1expander.hm"
echo. >>"hlp\mk1expander.hm"
echo // Resources (IDR_*) >>"hlp\mk1expander.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\mk1expander.hm"
echo. >>"hlp\mk1expander.hm"
echo // Dialogs (IDD_*) >>"hlp\mk1expander.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\mk1expander.hm"
echo. >>"hlp\mk1expander.hm"
echo // Frame Controls (IDW_*) >>"hlp\mk1expander.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\mk1expander.hm"
REM -- Make help for Project MK1EXPANDER


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\mk1expander.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\mk1expander.hlp" goto :Error
if not exist "hlp\mk1expander.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\mk1expander.hlp" Debug
if exist Debug\nul copy "hlp\mk1expander.cnt" Debug
if exist Release\nul copy "hlp\mk1expander.hlp" Release
if exist Release\nul copy "hlp\mk1expander.cnt" Release
echo.
goto :done

:Error
echo hlp\mk1expander.hpj(1) : error: Problem encountered creating help file

:done
echo.
