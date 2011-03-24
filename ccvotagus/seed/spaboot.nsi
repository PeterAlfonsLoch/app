; Script generated with the Venis Install Wizard



; Define your application name
!define APPNAME "spa"
!define APPNAMEANDVERSION "spa"

; Main Install settings
Name "${APPNAMEANDVERSION}"
InstallDir "C:\ca2\spaboot"
OutFile "V:\votagus\basis\stage\ccvotagus\Release\install_spaboot_extension_handler.exe"

; Use compression
SetCompressor Zlib

Section "spa"

	; Set Section properties
	SetOverwrite on

	; Set Section Files and Shortcuts
	SetOutPath "$INSTDIR\"
	File "..\..\..\stage\ccvotagus\Release\spaboot.exe"
	CreateDirectory "$SMPROGRAMS\spa"
	CreateShortCut "$SMPROGRAMS\spa\spa.lnk" "$INSTDIR\spaboot.exe"
  WriteRegStr HKEY_CLASSES_ROOT ".spaboot" "" "ccvotagus_ca2_spaboot_file"
	WriteRegStr HKEY_CLASSES_ROOT ".spaboot" "ContentType" "application/x-ccvotagus_ca2_spaboot_file"
  WriteRegStr HKEY_CLASSES_ROOT "ccvotagus_ca2_spaboot_file\shell" "" "open"
	WriteRegStr HKEY_CLASSES_ROOT "ccvotagus_ca2_spaboot_file\shell\open" "" "&Open"
	WriteRegStr HKEY_CLASSES_ROOT "ccvotagus_ca2_spaboot_file\shell\open\command" "" "$\"$INSTDIR\spaboot.exe$\" $\"%L$\""

SectionEnd

BrandingText "ccvotagus ca2 spaboot"

; eof