@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by LYRICSXTRACT.HPJ. >"hlp\lyricsxtract.hm"
echo. >>"hlp\lyricsxtract.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\lyricsxtract.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\lyricsxtract.hm"
echo. >>"hlp\lyricsxtract.hm"
echo // Prompts (IDP_*) >>"hlp\lyricsxtract.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\lyricsxtract.hm"
echo. >>"hlp\lyricsxtract.hm"
echo // Resources (IDR_*) >>"hlp\lyricsxtract.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\lyricsxtract.hm"
echo. >>"hlp\lyricsxtract.hm"
echo // Dialogs (IDD_*) >>"hlp\lyricsxtract.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\lyricsxtract.hm"
echo. >>"hlp\lyricsxtract.hm"
echo // Frame Controls (IDW_*) >>"hlp\lyricsxtract.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\lyricsxtract.hm"
REM -- Make help for Project LYRICSXTRACT


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\lyricsxtract.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\lyricsxtract.hlp" goto :Error
if not exist "hlp\lyricsxtract.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\lyricsxtract.hlp" Debug
if exist Debug\nul copy "hlp\lyricsxtract.cnt" Debug
if exist Release\nul copy "hlp\lyricsxtract.hlp" Release
if exist Release\nul copy "hlp\lyricsxtract.cnt" Release
echo.
goto :done

:Error
echo hlp\lyricsxtract.hpj(1) : error: Problem encountered creating help file

:done
echo.
