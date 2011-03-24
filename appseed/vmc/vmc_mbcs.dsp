# Microsoft Developer Studio Project File - Name="vmc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=vmc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vmc_mbcs.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vmc_mbcs.mak" CFG="vmc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vmc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "vmc - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "vmc - Win32 Release Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/vmc", AHBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vmc - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
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

!ELSEIF  "$(CFG)" == "vmc - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\vmsdb" /I "..\vmsgen" /I "..\vmsmus" /I "..\vmsgui" /I "..\vmsmix" /I "..\vmswave" /I "..\vmsgdi" /I "..\vmsp" /I "..\vmse" /I "..\vmsimg" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\_DebugMbcs/vmc.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "vmc - Win32 Release Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vmc___Win32_Release_Debug"
# PROP BASE Intermediate_Dir "vmc___Win32_Release_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\_ReleaseDebug"
# PROP Intermediate_Dir "ReleaseDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "VMSHOOK_EXPORTS" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
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

# Name "vmc - Win32 Release"
# Name "vmc - Win32 Debug"
# Name "vmc - Win32 Release Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BaseMDIChildWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BitmapWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Clef.cpp
# End Source File
# Begin Source File

SOURCE=.\CntrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\Color.cpp
# End Source File
# Begin Source File

SOURCE=.\containedcontrols.cpp
# End Source File
# Begin Source File

SOURCE=.\Debug.cpp
# End Source File
# Begin Source File

SOURCE=.\DEClef.cpp
# End Source File
# Begin Source File

SOURCE=.\DECoTimeNoteSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DEHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\DEKeySignature.cpp
# End Source File
# Begin Source File

SOURCE=.\DENote.cpp
# End Source File
# Begin Source File

SOURCE=.\DENoteSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DEPointSymbol.cpp
# End Source File
# Begin Source File

SOURCE=.\DERest.cpp
# End Source File
# Begin Source File

SOURCE=.\DESDLineSymbol.cpp
# End Source File
# Begin Source File

SOURCE=.\DEStaff.cpp
# End Source File
# Begin Source File

SOURCE=.\DEStaffSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DESymbolLine.cpp
# End Source File
# Begin Source File

SOURCE=.\DESymbolPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\DESymbolSDLine.cpp
# End Source File
# Begin Source File

SOURCE=.\DETimeSignature.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\DocumentBookmark.cpp
# End Source File
# Begin Source File

SOURCE=.\DocumentElement.cpp
# End Source File
# Begin Source File

SOURCE=.\DocumentEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\DocumentVisual.cpp
# End Source File
# Begin Source File

SOURCE=.\DVNote.cpp
# End Source File
# Begin Source File

SOURCE=.\DVSDLine.cpp
# End Source File
# Begin Source File

SOURCE=.\EditV017.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderSong.cpp
# End Source File
# Begin Source File

SOURCE=.\Keeper.cpp
# End Source File
# Begin Source File

SOURCE=.\KeySignature.cpp
# End Source File
# Begin Source File

SOURCE=.\ListBoxV1.cpp
# End Source File
# Begin Source File

SOURCE=.\LyricEvents.cpp
# End Source File
# Begin Source File

SOURCE=.\LyricEventV2.cpp
# End Source File
# Begin Source File

SOURCE=.\LyricType1Events.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Memory.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiEventsFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiEventsNoteEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiServerItem.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiTrackEventsView.cpp
# End Source File
# Begin Source File

SOURCE=.\MidiTracksEventsView.cpp
# End Source File
# Begin Source File

SOURCE=.\MSChunk.cpp
# End Source File
# Begin Source File

SOURCE=.\MSDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MSDocHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\MSEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\MSEventMidi.cpp
# End Source File
# Begin Source File

SOURCE=.\MSEvents.cpp
# End Source File
# Begin Source File

SOURCE=.\MSEventSymbol.cpp
# End Source File
# Begin Source File

SOURCE=.\MSFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MSHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\MSInPlaceFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MSMultiDocTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\MSMusic.cpp
# End Source File
# Begin Source File

SOURCE=.\MSNote.cpp
# End Source File
# Begin Source File

SOURCE=.\MSNotes.cpp
# End Source File
# Begin Source File

SOURCE=.\MSNoteUnit.cpp
# End Source File
# Begin Source File

SOURCE=.\MSPosition.cpp
# End Source File
# Begin Source File

SOURCE=.\MSPositions.cpp
# End Source File
# Begin Source File

SOURCE=.\MSQuantize.cpp
# End Source File
# Begin Source File

SOURCE=.\MSStaffView.cpp
# End Source File
# Begin Source File

SOURCE=.\MSTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\MSTrackV001.cpp
# End Source File
# Begin Source File

SOURCE=.\MSTrackV001Set.cpp
# End Source File
# Begin Source File

SOURCE=.\Music.cpp
# End Source File
# Begin Source File

SOURCE=.\MusicalBookmark.cpp
# End Source File
# Begin Source File

SOURCE=.\MusicalElement.cpp
# End Source File
# Begin Source File

SOURCE=.\MusicalVisual.cpp
# End Source File
# Begin Source File

SOURCE=.\MusicNote.cpp
# End Source File
# Begin Source File

SOURCE=.\MusicNoteDuration.cpp
# End Source File
# Begin Source File

SOURCE=.\MusicNotePitch.cpp
# End Source File
# Begin Source File

SOURCE=.\MusicRest.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsAudioDevicesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsImagesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsImagesDirectoriesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\Staff.cpp
# End Source File
# Begin Source File

SOURCE=.\StaffBookmark.cpp
# End Source File
# Begin Source File

SOURCE=.\StaffSet.cpp
# End Source File
# Begin Source File

SOURCE=.\StaffView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TimeSignature.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeArray.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeArrayElement.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeArrayLeaf.cpp
# End Source File
# Begin Source File

SOURCE=.\Uiutils.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\vmc.hpj

!IF  "$(CFG)" == "vmc - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__VMC_H="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\..\_ReleaseMbcs
TargetName=vmc_mbcs
InputPath=.\hlp\vmc.hpj
InputName=vmc

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vmc - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__VMC_H="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\..\_DebugMbcs
TargetName=vmc
InputPath=.\hlp\vmc.hpj
InputName=vmc

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vmc - Win32 Release Debug"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
USERDEP__VMC_H="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\..\_ReleaseDebug
TargetName=vmc_mbcs
InputPath=.\hlp\vmc.hpj
InputName=vmc

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\vmc.odl

!IF  "$(CFG)" == "vmc - Win32 Release"

!ELSEIF  "$(CFG)" == "vmc - Win32 Debug"

# ADD MTL /h "Vmc_i.h" /iid "Vmc_i.c"

!ELSEIF  "$(CFG)" == "vmc - Win32 Release Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\vmc.rc
# End Source File
# Begin Source File

SOURCE=.\Vmc_.cpp
# End Source File
# Begin Source File

SOURCE=.\VmcApp.cpp
# End Source File
# Begin Source File

SOURCE=.\vmcDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\VmcInPlaceFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\vmcView.cpp
# End Source File
# Begin Source File

SOURCE=.\VMSWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\WelcomeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\XfplayerDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\XfplayerOpenFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\XfplayerSaveFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\XfplayerScoring.cpp
# End Source File
# Begin Source File

SOURCE=.\XfplayerServerItem.cpp
# End Source File
# Begin Source File

SOURCE=.\XfplayerSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\XfplayerThreadV1.cpp
# End Source File
# Begin Source File

SOURCE=.\XfplayerThreadV2.cpp
# End Source File
# Begin Source File

SOURCE=.\XfplayerThreadV3.cpp
# End Source File
# Begin Source File

SOURCE=.\XfPropIHCommon1Dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\XfPropIHCommon2Dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\XfPropIHLanguageSpecific1Dialog.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AlbumDoc.h
# End Source File
# Begin Source File

SOURCE=.\BaseMDIChildWnd.h
# End Source File
# Begin Source File

SOURCE=.\BitmapWindow.h
# End Source File
# Begin Source File

SOURCE=.\ButtonV001.h
# End Source File
# Begin Source File

SOURCE=.\ButtonV007.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrame.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\Clef.h
# End Source File
# Begin Source File

SOURCE=.\CntrItem.h
# End Source File
# Begin Source File

SOURCE=.\Color.h
# End Source File
# Begin Source File

SOURCE=.\containedcontrols.h
# End Source File
# Begin Source File

SOURCE=.\dbdatacentral.h
# End Source File
# Begin Source File

SOURCE=.\Debug.h
# End Source File
# Begin Source File

SOURCE=.\DEClef.h
# End Source File
# Begin Source File

SOURCE=.\DECoTimeNoteSet.h
# End Source File
# Begin Source File

SOURCE=.\DEHeader.h
# End Source File
# Begin Source File

SOURCE=.\DEKeySignature.h
# End Source File
# Begin Source File

SOURCE=.\DENote.h
# End Source File
# Begin Source File

SOURCE=.\DENoteSet.h
# End Source File
# Begin Source File

SOURCE=.\DEPointSymbol.h
# End Source File
# Begin Source File

SOURCE=.\DERest.h
# End Source File
# Begin Source File

SOURCE=.\DESDLineSymbol.h
# End Source File
# Begin Source File

SOURCE=.\DEStaff.h
# End Source File
# Begin Source File

SOURCE=.\DEStaffSet.h
# End Source File
# Begin Source File

SOURCE=.\DESymbolLine.h
# End Source File
# Begin Source File

SOURCE=.\DESymbolPoint.h
# End Source File
# Begin Source File

SOURCE=.\DESymbolSDLine.h
# End Source File
# Begin Source File

SOURCE=.\DETimeSignature.h
# End Source File
# Begin Source File

SOURCE=.\DirectDraw.h
# End Source File
# Begin Source File

SOURCE=.\DocumentBookmark.h
# End Source File
# Begin Source File

SOURCE=.\DocumentElement.h
# End Source File
# Begin Source File

SOURCE=.\DocumentEvent.h
# End Source File
# Begin Source File

SOURCE=.\DocumentVisual.h
# End Source File
# Begin Source File

SOURCE=.\DVNote.h
# End Source File
# Begin Source File

SOURCE=.\DVSDLine.h
# End Source File
# Begin Source File

SOURCE=.\EditV017.h
# End Source File
# Begin Source File

SOURCE=.\ErrorDialog.h
# End Source File
# Begin Source File

SOURCE=.\FolderSong.h
# End Source File
# Begin Source File

SOURCE=.\Keeper.h
# End Source File
# Begin Source File

SOURCE=.\KeySignature.h
# End Source File
# Begin Source File

SOURCE=.\ListBoxV1.h
# End Source File
# Begin Source File

SOURCE=.\LyricEvents.h
# End Source File
# Begin Source File

SOURCE=.\LyricEventV2.h
# End Source File
# Begin Source File

SOURCE=.\LyricTrack.h
# End Source File
# Begin Source File

SOURCE=.\LyricTracks.h
# End Source File
# Begin Source File

SOURCE=.\LyricType1Events.h
# End Source File
# Begin Source File

SOURCE=.\LyricViewLine.h
# End Source File
# Begin Source File

SOURCE=.\LyricViewLines.h
# End Source File
# Begin Source File

SOURCE=.\LyricViewLineTemplate.h
# End Source File
# Begin Source File

SOURCE=.\LyricViewLineTemplates.h
# End Source File
# Begin Source File

SOURCE=.\MainFrame.h
# End Source File
# Begin Source File

SOURCE=.\Memory.h
# End Source File
# Begin Source File

SOURCE=.\MidiDoc.h
# End Source File
# Begin Source File

SOURCE=.\MidiEventsFrame.h
# End Source File
# Begin Source File

SOURCE=.\MidiEventsNoteEdit.h
# End Source File
# Begin Source File

SOURCE=.\MidiFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\MidiServerItem.h
# End Source File
# Begin Source File

SOURCE=.\MidiTrackEventsView.h
# End Source File
# Begin Source File

SOURCE=.\MidiTracksEventsView.h
# End Source File
# Begin Source File

SOURCE=.\MSChunk.h
# End Source File
# Begin Source File

SOURCE=.\MSDoc.h
# End Source File
# Begin Source File

SOURCE=.\MSDocHeader.h
# End Source File
# Begin Source File

SOURCE=.\MSEvent.h
# End Source File
# Begin Source File

SOURCE=.\MSEventMidi.h
# End Source File
# Begin Source File

SOURCE=.\MSEvents.h
# End Source File
# Begin Source File

SOURCE=.\MSEventSymbol.h
# End Source File
# Begin Source File

SOURCE=.\MSFrame.h
# End Source File
# Begin Source File

SOURCE=.\MSHeader.h
# End Source File
# Begin Source File

SOURCE=.\MSInPlaceFrame.h
# End Source File
# Begin Source File

SOURCE=.\MSMultiDocTemplate.h
# End Source File
# Begin Source File

SOURCE=.\MSMusic.h
# End Source File
# Begin Source File

SOURCE=.\MSNote.h
# End Source File
# Begin Source File

SOURCE=.\MSNotes.h
# End Source File
# Begin Source File

SOURCE=.\MSNoteUnit.h
# End Source File
# Begin Source File

SOURCE=.\MSPosition.h
# End Source File
# Begin Source File

SOURCE=.\MSPositions.h
# End Source File
# Begin Source File

SOURCE=.\MSQuantize.h
# End Source File
# Begin Source File

SOURCE=.\MSStaffView.h
# End Source File
# Begin Source File

SOURCE=.\MSTrack.h
# End Source File
# Begin Source File

SOURCE=.\MSTrackV001.h
# End Source File
# Begin Source File

SOURCE=.\MSTrackV001Set.h
# End Source File
# Begin Source File

SOURCE=.\Music.h
# End Source File
# Begin Source File

SOURCE=.\MusicalBookmark.h
# End Source File
# Begin Source File

SOURCE=.\MusicalElement.h
# End Source File
# Begin Source File

SOURCE=.\MusicalVisual.h
# End Source File
# Begin Source File

SOURCE=.\MusicNote.h
# End Source File
# Begin Source File

SOURCE=.\MusicNoteDuration.h
# End Source File
# Begin Source File

SOURCE=.\MusicNotePitch.h
# End Source File
# Begin Source File

SOURCE=.\MusicRest.h
# End Source File
# Begin Source File

SOURCE=.\OptionsAudioDevicesDialog.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDialog.h
# End Source File
# Begin Source File

SOURCE=.\OptionsImagesDialog.h
# End Source File
# Begin Source File

SOURCE=.\OptionsImagesDirectoriesDialog.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SingleDocTemplateV003.h
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.h
# End Source File
# Begin Source File

SOURCE=.\Staff.h
# End Source File
# Begin Source File

SOURCE=.\StaffBookmark.h
# End Source File
# Begin Source File

SOURCE=.\StaffSet.h
# End Source File
# Begin Source File

SOURCE=.\StaffView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Timer.h
# End Source File
# Begin Source File

SOURCE=.\TimeSignature.h
# End Source File
# Begin Source File

SOURCE=.\TreeArray.h
# End Source File
# Begin Source File

SOURCE=.\TreeArrayElement.h
# End Source File
# Begin Source File

SOURCE=.\TreeArrayLeaf.h
# End Source File
# Begin Source File

SOURCE=.\Uiutils.h
# End Source File
# Begin Source File

SOURCE=.\vmc_.h
# End Source File
# Begin Source File

SOURCE=.\vmc_i.h
# End Source File
# Begin Source File

SOURCE=.\VmcApp.h
# End Source File
# Begin Source File

SOURCE=.\vmcDoc.h
# End Source File
# Begin Source File

SOURCE=.\VmcInPlaceFrame.h
# End Source File
# Begin Source File

SOURCE=.\VmcResource.h
# End Source File
# Begin Source File

SOURCE=.\vmcView.h
# End Source File
# Begin Source File

SOURCE=.\VMS_.H
# End Source File
# Begin Source File

SOURCE=.\VMSWriter.h
# End Source File
# Begin Source File

SOURCE=.\WelcomeDialog.h
# End Source File
# Begin Source File

SOURCE=.\WndAppearanceV033.h
# End Source File
# Begin Source File

SOURCE=.\WndFrameworkV033.h
# End Source File
# Begin Source File

SOURCE=.\WndMovingManager.h
# End Source File
# Begin Source File

SOURCE=.\WndSizingManagerV033.h
# End Source File
# Begin Source File

SOURCE=.\WndSysMenuManagerV033.h
# End Source File
# Begin Source File

SOURCE=.\XfplayerDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\XfplayerOpenFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\XfplayerSaveFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\XfplayerScoring.h
# End Source File
# Begin Source File

SOURCE=.\XfplayerServerItem.h
# End Source File
# Begin Source File

SOURCE=.\XfplayerSlider.h
# End Source File
# Begin Source File

SOURCE=.\XfplayerThreadV1.h
# End Source File
# Begin Source File

SOURCE=.\XfplayerThreadV2.h
# End Source File
# Begin Source File

SOURCE=.\XfplayerThreadV3.h
# End Source File
# Begin Source File

SOURCE=.\XfPropIHCommon1Dialog.h
# End Source File
# Begin Source File

SOURCE=.\XfPropIHCommon2Dialog.h
# End Source File
# Begin Source File

SOURCE=.\XfPropIHLanguageSpecific1Dialog.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\IToolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menuv033.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\vmc.ico
# End Source File
# Begin Source File

SOURCE=.\res\vmc.rc2
# End Source File
# Begin Source File

SOURCE=.\Vmc.rgs
# End Source File
# Begin Source File

SOURCE=.\res\vmcDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\vmcsplash1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\xfplayer.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxOleCl.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxOleSv.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\vmc.cnt

!IF  "$(CFG)" == "vmc - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\..\_ReleaseMbcs
InputPath=.\hlp\vmc.cnt
InputName=vmc

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "vmc - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\..\_DebugMbcs
InputPath=.\hlp\vmc.cnt
InputName=vmc

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "vmc - Win32 Release Debug"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\..\_ReleaseDebug
InputPath=.\hlp\vmc.cnt
InputName=vmc

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\vmc.reg
# End Source File
# Begin Source File

SOURCE=.\vmsidle.tlh
# End Source File
# Begin Source File

SOURCE=.\vmsidle.tli
# End Source File
# End Target
# End Project
