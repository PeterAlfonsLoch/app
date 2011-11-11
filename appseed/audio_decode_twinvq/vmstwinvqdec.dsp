# Microsoft Developer Studio Project File - Name="vmstwinvqdec" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=vmstwinvqdec - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vmstwinvqdec.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vmstwinvqdec.mak" CFG="vmstwinvqdec - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vmstwinvqdec - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vmstwinvqdec - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vmstwinvqdec - Win32 Release Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/vmstwinvqdec", UPDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vmstwinvqdec - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../vmsaudioi" /I "../vmsgen" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_VMSTWINVQDEC_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tvqdec.lib /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT LINK32 /profile /map /debug

!ELSEIF  "$(CFG)" == "vmstwinvqdec - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../_MbcsDebug"
# PROP Intermediate_Dir "../_MbcsDebug/_intermediate/vmstwinvqdec"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../vmsaudioi" /I "../vmsgen" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_VMSTWINVQDEC_DLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 tvqdec.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "vmstwinvqdec - Win32 Release Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release Debug"
# PROP BASE Intermediate_Dir "Release Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../_MbcsReleaseDebug"
# PROP Intermediate_Dir "_MbcsReleaseDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../vmsaudioi" /I "../vmsgen" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "_VMSTWINVQDEC_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_VMSCDADEC_DLL" /D "FIXED_POINT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tvqdec.lib /nologo /subsystem:windows /dll /profile /map /debug /machine:I386

!ENDIF 

# Begin Target

# Name "vmstwinvqdec - Win32 Release"
# Name "vmstwinvqdec - Win32 Debug"
# Name "vmstwinvqdec - Win32 Release Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\_vmstwinvqdecDecoder.cpp
# End Source File
# Begin Source File

SOURCE=.\_vmstwinvqdecTwinVQ.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\vmstwinvqdec.cpp
# End Source File
# Begin Source File

SOURCE=.\vmstwinvqdec.def
# End Source File
# Begin Source File

SOURCE=.\vmstwinvqdec.odl
# End Source File
# Begin Source File

SOURCE=.\vmstwinvqdec.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\_vmstwinvqdec.h
# End Source File
# Begin Source File

SOURCE=.\_vmstwinvqdecDecoder.h
# End Source File
# Begin Source File

SOURCE=.\_vmstwinvqdecTwinVQ.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\vmstwinvqdec.rc2
# End Source File
# End Group
# Begin Group "Source TestDec"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bfile.cxx

!IF  "$(CFG)" == "vmstwinvqdec - Win32 Release"

!ELSEIF  "$(CFG)" == "vmstwinvqdec - Win32 Debug"

# ADD CPP /W1 /Yu

!ELSEIF  "$(CFG)" == "vmstwinvqdec - Win32 Release Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\bstream.cxx

!IF  "$(CFG)" == "vmstwinvqdec - Win32 Release"

!ELSEIF  "$(CFG)" == "vmstwinvqdec - Win32 Debug"

# ADD CPP /W1 /Yu

!ELSEIF  "$(CFG)" == "vmstwinvqdec - Win32 Release Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Chunk.cxx

!IF  "$(CFG)" == "vmstwinvqdec - Win32 Release"

!ELSEIF  "$(CFG)" == "vmstwinvqdec - Win32 Debug"

# ADD CPP /W1 /Yu

!ELSEIF  "$(CFG)" == "vmstwinvqdec - Win32 Release Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\decoder.cxx

!IF  "$(CFG)" == "vmstwinvqdec - Win32 Release"

!ELSEIF  "$(CFG)" == "vmstwinvqdec - Win32 Debug"

# ADD CPP /W1 /Yu

!ELSEIF  "$(CFG)" == "vmstwinvqdec - Win32 Release Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HeaderManager.cxx

!IF  "$(CFG)" == "vmstwinvqdec - Win32 Release"

!ELSEIF  "$(CFG)" == "vmstwinvqdec - Win32 Debug"

# ADD CPP /W1 /Yu

!ELSEIF  "$(CFG)" == "vmstwinvqdec - Win32 Release Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header TestDec"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bfile.h
# End Source File
# Begin Source File

SOURCE=.\bstream.h
# End Source File
# Begin Source File

SOURCE=.\Chunk.h
# End Source File
# Begin Source File

SOURCE=.\HeaderManager.h
# End Source File
# Begin Source File

SOURCE=.\tvqdec.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
