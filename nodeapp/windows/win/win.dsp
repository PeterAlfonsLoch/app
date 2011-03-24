# Microsoft Developer Studio Project File - Name="win" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=win - Win32 basis
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "win.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "win.mak" CFG="win - Win32 basis"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "win - Win32 basis" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "basis"
# PROP BASE Intermediate_Dir "basis"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../stage/vc6/"
# PROP Intermediate_Dir "../../../time/intermediate/vc6/win"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "WIN_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D "WIN_EXPORTS" /D "VC6" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX"StdAfx.h" /FD /GZ /Zm1024 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /pdbtype:sept
# Begin Target

# Name "win - Win32 basis"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\_vmswin.2.h
# End Source File
# Begin Source File

SOURCE=.\_vmswin_afxwin_.h
# End Source File
# Begin Source File

SOURCE=.\_vmswinAppImpl.2.h
# End Source File
# Begin Source File

SOURCE=.\_vmswinFrameWndInterface.2.h
# End Source File
# Begin Source File

SOURCE=.\AfxImpl.H
# End Source File
# Begin Source File

SOURCE=.\application.h
# End Source File
# Begin Source File

SOURCE=.\bitmap.h
# End Source File
# Begin Source File

SOURCE=.\brush.h
# End Source File
# Begin Source File

SOURCE=.\dib.h
# End Source File
# Begin Source File

SOURCE=.\dir.h
# End Source File
# Begin Source File

SOURCE=.\draw_dib.h
# End Source File
# Begin Source File

SOURCE=.\factory_exchange.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\gen_1.h
# End Source File
# Begin Source File

SOURCE=.\graphics.h
# End Source File
# Begin Source File

SOURCE=.\graphics_object.h
# End Source File
# Begin Source File

SOURCE=.\handle.h
# End Source File
# Begin Source File

SOURCE=.\implementation.h
# End Source File
# Begin Source File

SOURCE=.\osi.h
# End Source File
# Begin Source File

SOURCE=.\palette.h
# End Source File
# Begin Source File

SOURCE=.\pen.h
# End Source File
# Begin Source File

SOURCE=.\rgn.h
# End Source File
# Begin Source File

SOURCE=.\state.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\thread.h
# End Source File
# Begin Source File

SOURCE=.\thread_slots.h
# End Source File
# Begin Source File

SOURCE=.\UACTools.h
# End Source File
# Begin Source File

SOURCE=.\WFileFind.h
# End Source File
# Begin Source File

SOURCE=.\win.h
# End Source File
# Begin Source File

SOURCE=.\win1.h
# End Source File
# Begin Source File

SOURCE=.\win_internal.h
# End Source File
# Begin Source File

SOURCE=.\WinBitmap.h
# End Source File
# Begin Source File

SOURCE=.\WinBrush.h
# End Source File
# Begin Source File

SOURCE=.\WinClientDC.h
# End Source File
# Begin Source File

SOURCE=.\WinDC.h
# End Source File
# Begin Source File

SOURCE=.\window.h
# End Source File
# Begin Source File

SOURCE=.\window_draw.h
# End Source File
# Begin Source File

SOURCE=.\WindowsShell.h
# End Source File
# Begin Source File

SOURCE=.\WinEx1Factory.h
# End Source File
# Begin Source File

SOURCE=.\WinFile.h
# End Source File
# Begin Source File

SOURCE=.\WinFileSet.h
# End Source File
# Begin Source File

SOURCE=.\WinFileSystem.h
# End Source File
# Begin Source File

SOURCE=.\WinFont.h
# End Source File
# Begin Source File

SOURCE=.\WinGdiObject.h
# End Source File
# Begin Source File

SOURCE=.\WinPaintDC.h
# End Source File
# Begin Source File

SOURCE=.\WinPalette.h
# End Source File
# Begin Source File

SOURCE=.\WinPen.h
# End Source File
# Begin Source File

SOURCE=.\WinResource.h
# End Source File
# Begin Source File

SOURCE=.\WinRgn.h
# End Source File
# Begin Source File

SOURCE=.\WinStdioFile.h
# End Source File
# Begin Source File

SOURCE=.\WinWindowDC.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
