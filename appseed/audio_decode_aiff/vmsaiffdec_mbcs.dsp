# Microsoft Developer Studio Project File - Name="vmsaiffdec" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=vmsaiffdec - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vmsaiffdec_mbcs.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vmsaiffdec_mbcs.mak" CFG="vmsaiffdec - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vmsaiffdec - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vmsaiffdec - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vmsaiffdec - Win32 Release Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/vmsaiffdec", VQDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vmsaiffdec - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../vmsgen" /I "../vmsaudioi" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_VMSAIFFDEC_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"../_MbcsRelease/vmsaiffdec.dll"

!ELSEIF  "$(CFG)" == "vmsaiffdec - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../_MbcsDebug"
# PROP Intermediate_Dir "../_MbcsDebug/_intermediate/vmsaiffdec"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../vmsgen" /I "../vmsaudioi" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_VMSAIFFDEC_DLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../_MbcsDebug/vmsaiffdec.dll" /pdbtype:sept

!ELSEIF  "$(CFG)" == "vmsaiffdec - Win32 Release Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vmsaiffdec___Win32_Release_Debug"
# PROP BASE Intermediate_Dir "vmsaiffdec___Win32_Release_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../_MbcsReleaseDebug"
# PROP Intermediate_Dir "_MbcsReleaseDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../vmsgen" /I "../vmsaudioi" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_VMSAIFFDEC_DLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../vmsgen" /I "../vmsaudioi" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "_VMSAIFFDEC_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_VMSCDADEC_DLL" /D "FIXED_POINT" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /profile /map /debug /machine:I386 /out:"../_MbcsReleaseDebug/vmsaiffdec.dll"

!ENDIF 

# Begin Target

# Name "vmsaiffdec - Win32 Release"
# Name "vmsaiffdec - Win32 Debug"
# Name "vmsaiffdec - Win32 Release Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\_vmsaiffdecChunk.cpp
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecChunkHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecCommonChunk.cpp
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecDecoder.cpp
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecExtended.cpp
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecFormChunk.cpp
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecID.cpp
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecSoundDataChunk.cpp
# End Source File
# Begin Source File

SOURCE=.\ieeefloat.c

!IF  "$(CFG)" == "vmsaiffdec - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "vmsaiffdec - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "vmsaiffdec - Win32 Release Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\vmsaiffdec.cpp
# End Source File
# Begin Source File

SOURCE=.\vmsaiffdec.def
# End Source File
# Begin Source File

SOURCE=.\vmsaiffdec.odl
# End Source File
# Begin Source File

SOURCE=.\vmsaiffdec.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\_vmsaiffdec.h
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecChunk.h
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecChunkHeader.h
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecCommonChunk.h
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecDecoder.h
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecExtended.h
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecFormChunk.h
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecID.h
# End Source File
# Begin Source File

SOURCE=.\_vmsaiffdecSoundDataChunk.h
# End Source File
# Begin Source File

SOURCE=.\ieeefloat.h
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

SOURCE=.\res\vmsaiffdec.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
