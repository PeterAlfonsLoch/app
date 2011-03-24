# Microsoft Developer Studio Project File - Name="vmse" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=vmse - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vmse_mbcs.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vmse_mbcs.mak" CFG="vmse - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vmse - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vmse - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vmse - Win32 Release Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/vmse", GRAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vmse - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\_ReleaseMbcs"
# PROP Intermediate_Dir "_ReleaseMbcs"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "..\vmsgen" /I "..\vmsmus" /I "..\vmsgui" /I "..\vmsp" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_VMSE_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"..\_ReleaseMbcs/vmse.dll"

!ELSEIF  "$(CFG)" == "vmse - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\_DebugMbcs"
# PROP Intermediate_Dir "_DebugMbcs"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\vmsgen" /I "..\vmsmus" /I "..\vmsgui" /I "..\vmsp" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_VMSE_DLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 vmsmus.lib vmsp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"msvcrt.lib" /out:"..\_DebugMbcs/vmse.dll" /pdbtype:sept /libpath:"..\_Debug"

!ELSEIF  "$(CFG)" == "vmse - Win32 Release Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vmse___Win32_Release_Debug"
# PROP BASE Intermediate_Dir "vmse___Win32_Release_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\_ReleaseDebug"
# PROP Intermediate_Dir "ReleaseDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\vmsgen" /I "..\vmsmus" /I "..\vmsgui" /I "..\vmsp" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_VMSE_DLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../vmsdbi" /I "../vmsgdi" /I "../vmsgen" /I "../vmsguii" /I "../vmsmediai" /I "../vmsmus" /I "../vmsguibase" /I "../vmssimpledb" /I "../vmssqlite" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_VMSE_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386

!ENDIF 

# Begin Target

# Name "vmse - Win32 Release"
# Name "vmse - Win32 Debug"
# Name "vmse - Win32 Release Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CntrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\IpFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiEventsNoteEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiTrackEventsView.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiTracksEventsView.cpp
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VmeApp.cpp
# End Source File
# Begin Source File

SOURCE=.\vmeDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\VmeFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\VmeTreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\VmeView.cpp
# End Source File
# Begin Source File

SOURCE=.\VmeViewUpdateHint.cpp
# End Source File
# Begin Source File

SOURCE=.\vmse.cpp
# End Source File
# Begin Source File

SOURCE=.\vmse.def
# End Source File
# Begin Source File

SOURCE=.\vmse.odl
# End Source File
# Begin Source File

SOURCE=.\vmse.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CntrItem.h
# End Source File
# Begin Source File

SOURCE=.\IpFrame.h
# End Source File
# Begin Source File

SOURCE=.\MainFrame.h
# End Source File
# Begin Source File

SOURCE=.\MidiDoc.h
# End Source File
# Begin Source File

SOURCE=.\MidiEventsNoteEdit.h
# End Source File
# Begin Source File

SOURCE=.\MidiFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\MidiTrackEventsView.h
# End Source File
# Begin Source File

SOURCE=.\MidiTracksEventsView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VmeApp.h
# End Source File
# Begin Source File

SOURCE=.\vmeDoc.h
# End Source File
# Begin Source File

SOURCE=.\VmeFrame.h
# End Source File
# Begin Source File

SOURCE=.\VmeTreeView.h
# End Source File
# Begin Source File

SOURCE=.\VmeView.h
# End Source File
# Begin Source File

SOURCE=.\VmeViewUpdateHint.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\Cópia de vms splash 7.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\IToolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\vme.ico
# End Source File
# Begin Source File

SOURCE=.\res\vmeDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\vmse.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
