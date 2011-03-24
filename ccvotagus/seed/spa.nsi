; Script generated with the Venis Install Wizard



; Define your application name
!define APPNAME "spa"
!define APPNAMEANDVERSION "spa"

; Main Install settings
Name "${APPNAMEANDVERSION}"
InstallDir "$PROGRAMFILES\ca2\spa"
OutFile "V:\votagus\basis\stage\ccvotagus\Release\install_spaadmin_extension_handler.exe"

; Use compression
SetCompressor Zlib

Section "spa"

	; Set Section properties
	SetOverwrite on

	; Set Section Files and Shortcuts
	SetOutPath "$INSTDIR\"
	File "..\..\..\stage\ccvotagus\Release\spaadmin.exe"
	CreateDirectory "$SMPROGRAMS\spa"
	CreateShortCut "$SMPROGRAMS\spa\spa.lnk" "$INSTDIR\spaadmin.exe"
  WriteRegStr HKEY_CLASSES_ROOT ".spaadmin" "" "ccvotagus_ca2_spaadmin_file"
  WriteRegStr HKEY_CLASSES_ROOT "ccvotagus_ca2_spaadmin_file\shell" "" "open"
	WriteRegStr HKEY_CLASSES_ROOT "ccvotagus_ca2_spaadmin_file\shell\open" "" "&Open"
	WriteRegStr HKEY_CLASSES_ROOT "ccvotagus_ca2_spaadmin_file\shell\open\command" "" "$\"$INSTDIR\spaadmin.exe$\" $\"%L$\""

SectionEnd

BrandingText "ccvotagus ca2 spa"

; eof