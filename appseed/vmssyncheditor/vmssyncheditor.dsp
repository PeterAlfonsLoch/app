# Microsoft Developer Studio Project File - Name="vmssyncheditor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=vmssyncheditor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vmssyncheditor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vmssyncheditor.mak" CFG="vmssyncheditor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vmssyncheditor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "vmssyncheditor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "vmssyncheditor - Win32 Release Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/vmssyncheditor", YCDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vmssyncheditor - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../_MbcsRelease"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../vmsaudio" /I "../vmsdbi" /I "../vmsgcom" /I "../vmsgdi" /I "../vmsgen" /I "../vmsguiex" /I "../vmsguii" /I "../vmsimg" /I "../vmssimpledb" /I "../vmsguibase" /I "../vmsmus" /I "../vmsmusctrl" /I "../vmskar" /I "../vmskaraokei" /I "../vmszip" /I "../vmsmediai" /I "../vmsmediamanageri" /I "../vmsmediaplay" /I "../vmspl" /I "../vmssqlite" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /profile /map /debug

!ELSEIF  "$(CFG)" == "vmssyncheditor - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../_MbcsDebug"
# PROP Intermediate_Dir "../_MbcsDebug/_intermediate/vmssyncheditor"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../vmsaudio" /I "../vmsdbi" /I "../vmsgcom" /I "../vmsgdi" /I "../vmsgen" /I "../vmsguiex" /I "../vmsguii" /I "../vmsimg" /I "../vmssimpledb" /I "../vmsguibase" /I "../vmsmus" /I "../vmsmusctrl" /I "../vmskar" /I "../vmskaraokei" /I "../vmszip" /I "../vmsmediai" /I "../vmsmediamanageri" /I "../vmsmediaplay" /I "../vmspl" /I "../vmssqlite" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libsigc++1.2-vc6.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "vmssyncheditor - Win32 Release Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vmssyncheditor___Win32_Release_Debug"
# PROP BASE Intermediate_Dir "vmssyncheditor___Win32_Release_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../_MbcsReleaseDebug"
# PROP Intermediate_Dir "_MbcsReleaseDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /I "../vmsdbi" /I "../vmsgcom" /I "../vmsgdi" /I "../vmsgen" /I "../vmsguii" /I "../vmssimpledb" /I "../vmsguibase" /I "../vmsmus" /I "../vmsmusctrl" /I "../vmskar" /I "../vmskaraokei" /I "../vmszip" /I "../vmsmediai" /I "../vmsmediamanageri" /I "../vmsmediaplay" /I "../vmspl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../vmsaudio" /I "../vmsdbi" /I "../vmsgcom" /I "../vmsgdi" /I "../vmsgen" /I "../vmsguiex" /I "../vmsguii" /I "../vmsimg" /I "../vmssimpledb" /I "../vmsguibase" /I "../vmsmus" /I "../vmsmusctrl" /I "../vmskar" /I "../vmskaraokei" /I "../vmszip" /I "../vmsmediai" /I "../vmsmediamanageri" /I "../vmsmediaplay" /I "../vmspl" /I "../vmssqlite" /D "_AFXDLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_VMSCDADEC_DLL" /D "FIXED_POINT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "vmssyncheditor - Win32 Release"
# Name "vmssyncheditor - Win32 Debug"
# Name "vmssyncheditor - Win32 Release Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\_vmssyncheditorDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\_vmssyncheditorView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiTrackSelectControlInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiTrackSelectDDX.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiTrackSelectDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiTrackSelectFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiTrackSelectInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiTrackSelectView.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiTrackSelectViewUpdateHint.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SynchEditorMediaView.cpp
# End Source File
# Begin Source File

SOURCE=.\SynchEditorTokenListView.cpp
# End Source File
# Begin Source File

SOURCE=.\SynchEditorView1.cpp
# End Source File
# Begin Source File

SOURCE=.\vmssyncheditor.cpp
# End Source File
# Begin Source File

SOURCE=.\vmssyncheditor.odl
# End Source File
# Begin Source File

SOURCE=.\vmssyncheditor.rc
# End Source File
# Begin Source File

SOURCE=.\XfplayerOpenFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\XfplayerSaveFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\XView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\_vmssyncheditorDoc.h
# End Source File
# Begin Source File

SOURCE=.\_vmssyncheditorView.h
# End Source File
# Begin Source File

SOURCE=.\_vmssyncheditorVmsDataKey.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MidiTrackSelectControlInterface.h
# End Source File
# Begin Source File

SOURCE=.\MidiTrackSelectDDX.h
# End Source File
# Begin Source File

SOURCE=.\MidiTrackSelectDoc.h
# End Source File
# Begin Source File

SOURCE=.\MidiTrackSelectFrame.h
# End Source File
# Begin Source File

SOURCE=.\MidiTrackSelectInterface.h
# End Source File
# Begin Source File

SOURCE=.\MidiTrackSelectView.h
# End Source File
# Begin Source File

SOURCE=.\MidiTrackSelectViewUpdateHint.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "vmssyncheditor - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=vmssyncheditor
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vmssyncheditor - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=vmssyncheditor
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vmssyncheditor - Win32 Release Debug"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=vmssyncheditor
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SynchEditorMediaView.h
# End Source File
# Begin Source File

SOURCE=.\SynchEditorTokenListView.h
# End Source File
# Begin Source File

SOURCE=.\SynchEditorView1.h
# End Source File
# Begin Source File

SOURCE=.\vmssyncheditor.h
# End Source File
# Begin Source File

SOURCE=.\XfplayerOpenFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\XfplayerSaveFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\XView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\_vmssyncheditorDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\vmssyncheditor.ico
# End Source File
# Begin Source File

SOURCE=.\res\vmssyncheditor.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\vmssyncheditor.reg
# End Source File
# End Target
# End Project
