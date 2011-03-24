# Microsoft Developer Studio Project File - Name="vmscdp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=vmscdp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vmscdp_mbcs.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vmscdp_mbcs.mak" CFG="vmscdp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vmscdp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vmscdp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vmscdp - Win32 Release Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/vmscdp", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vmscdp - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "..\vmsgen" /I "..\vmsmus" /I "..\vmsdb" /I "..\vmsgui" /I "..\vmswave" /I "..\vmsmix" /I "..\vmsimg" /I "..\vmsgdi" /I "../vmsgen" /I "../vmsmus" /I "../vmsdb" /I "../vmsgui" /I "../vmswave" /I "../vmsmix" /I "../vmsimg" /I "../vmsgdi" /I "../vmsgcom" /I "../vmspl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_vmscdp_DLL" /FR /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 FreeImage.lib winmm.lib nsp.lib /nologo /subsystem:windows /dll /pdb:none /map /machine:I386 /out:"..\_ReleaseUnicode/vmscdp.dll"

!ELSEIF  "$(CFG)" == "vmscdp - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../_MbcsDebug"
# PROP Intermediate_Dir "_MbcsDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../vmsgen" /I "../vmsmus" /I "../vmsdb" /I "../vmsgui" /I "../vmswave" /I "../vmsmix" /I "../vmsimg" /I "../vmsgdi" /I "../vmsgcom" /I "../vmspl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_vmscdp_DLL" /FR /Yu"StdAfx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib nsp.lib msword9.lib htmlhelp.lib /nologo /subsystem:windows /dll /profile /map /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"msvcrt.lib" /out:"..\_DebugMbcs/vmscdp.dll" /libpath:"..\_DebugMbcs"

!ELSEIF  "$(CFG)" == "vmscdp - Win32 Release Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vmscdp___Win32_Release_Debug"
# PROP BASE Intermediate_Dir "vmscdp___Win32_Release_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../_MbcsReleaseDebug"
# PROP Intermediate_Dir "_MbcsReleaseDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O1 /I "..\vmsgen" /I "..\vmsmus" /I "..\vmsdb" /I "..\vmsgui" /I "..\vmswave" /I "..\vmsmix" /I "..\vmsimg" /I "..\vmsgdi" /I "..\vakrip" /I "..\vmsp" /I "../vmsgen" /I "../vmsmus" /I "../vmsdb" /I "../vmsgui" /I "../vmswave" /I "../vmsmix" /I "../vmsimg" /I "../vmsgdi" /I "../vmsgcom" /I "../vmspl" /D "_WINDLL" /D "_AFXEXT" /D "vmscdp_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "VMSHOOK_EXPORTS" /D "_vmscdp_DLL" /FR"_ReleaseDebugMbcs/" /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 FreeImage.lib winmm.lib nsp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"msvcrtd.lib"

!ENDIF 

# Begin Target

# Name "vmscdp - Win32 Release"
# Name "vmscdp - Win32 Debug"
# Name "vmscdp - Win32 Release Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CDDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\CDFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\CDView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "vmscdp - Win32 Release"

!ELSEIF  "$(CFG)" == "vmscdp - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "vmscdp - Win32 Release Debug"

# ADD CPP /Yc"StdAfx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VcdpApp.cpp
# End Source File
# Begin Source File

SOURCE=.\vmscdp.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CDDoc.h
# End Source File
# Begin Source File

SOURCE=.\CDFrame.h
# End Source File
# Begin Source File

SOURCE=.\CDView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VcdpApp.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\album.bmp
# End Source File
# Begin Source File

SOURCE=.\res\album1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\album1.ico
# End Source File
# Begin Source File

SOURCE=.\res\album2.ico
# End Source File
# Begin Source File

SOURCE=.\res\album_sm.bmp
# End Source File
# Begin Source File

SOURCE=.\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\res\bb3.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00011.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00012.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Cópia de vms splash 7.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\error.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00012.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00013.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00014.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00015.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00016.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\idi_.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_dde.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_xfpl.ico
# End Source File
# Begin Source File

SOURCE=.\res\IToolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\menuv033.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\Vmp.rgs
# End Source File
# Begin Source File

SOURCE=.\res\vmpsplash7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\vms1.bin
# End Source File
# Begin Source File

SOURCE=.\res\vmscdp.rc2
# End Source File
# Begin Source File

SOURCE=.\res\vmssplash7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\xfplayer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\xfplayer.ico
# End Source File
# Begin Source File

SOURCE=.\Xfplayer.rgs
# End Source File
# Begin Source File

SOURCE=.\res\xfplayerDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\Clean\Album\index.html
# End Source File
# Begin Source File

SOURCE=".\clean\Álbum\index.html"
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\vmp.emf
# End Source File
# Begin Source File

SOURCE=.\res\vmp447cv.emf
# End Source File
# Begin Source File

SOURCE=.\res\vmpcoolgray.emf
# End Source File
# End Target
# End Project
