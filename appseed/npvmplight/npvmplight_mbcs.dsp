# Microsoft Developer Studio Project File - Name="npvmplight" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=npvmplight - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "npvmplight_mbcs.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "npvmplight_mbcs.mak" CFG="npvmplight - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "npvmplight - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "npvmplight - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/npvmplight", KUBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "npvmplight - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../_MbcsRelease"
# PROP Intermediate_Dir "_MbcsRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "netscape" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_NPVMP_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"../_MbcsRelease/npvmplight.dll"

!ELSEIF  "$(CFG)" == "npvmplight - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../_prod/_MbcsDebug"
# PROP Intermediate_Dir "../../_prod/_MbcsDebug_intermediate/npvmplight"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "netscape" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_NPVMP_DLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../_MbcsDebug/npvmplight.dll" /pdbtype:sept
# Begin Custom Build
InputPath=\veriwell\_project\_MbcsDebug\npvmplight.dll
InputName=npvmplight
SOURCE="$(InputPath)"

"C:\Arquivos de programas\Mozilla Firefox\plugins\$(InputName)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) "C:\Arquivos de programas\Mozilla Firefox\plugins"

# End Custom Build

!ENDIF 

# Begin Target

# Name "npvmplight - Win32 Release"
# Name "npvmplight - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\NPPData.cpp
# End Source File
# Begin Source File

SOURCE=.\npvmplight.cpp
# End Source File
# Begin Source File

SOURCE=.\npvmplight.def
# End Source File
# Begin Source File

SOURCE=.\npvmplight.odl
# End Source File
# Begin Source File

SOURCE=.\npvmplight.rc
# End Source File
# Begin Source File

SOURCE=.\npvmpLightCntrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\npvmpLightDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\NpvmpLightFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\npvmpLightView.cpp
# End Source File
# Begin Source File

SOURCE=.\OleServerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SavedData.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\vmsp.cpp
# End Source File
# Begin Source File

SOURCE=.\vmsx173.cpp
# End Source File
# Begin Source File

SOURCE=.\Vmsx173Ctl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\NPPData.h
# End Source File
# Begin Source File

SOURCE=.\npvmplight.h
# End Source File
# Begin Source File

SOURCE=.\npvmpLightCntrItem.h
# End Source File
# Begin Source File

SOURCE=.\npvmpLightDoc.h
# End Source File
# Begin Source File

SOURCE=.\NpvmpLightFrame.h
# End Source File
# Begin Source File

SOURCE=.\npvmpLightView.h
# End Source File
# Begin Source File

SOURCE=.\OleServerDoc.h
# End Source File
# Begin Source File

SOURCE=.\OleWnd.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SavedData.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\vmsp.h
# End Source File
# Begin Source File

SOURCE=.\vmsx173.h
# End Source File
# Begin Source File

SOURCE=.\Vmsx173Ctl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\npvmplight.rc2
# End Source File
# Begin Source File

SOURCE=.\Vmsx173Ctl.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
