call "%VS_VARS%"

cd "%VOTAGUS_ROOT%appseed\ca2\fontopus\net\ds\common\netnode\"

cl /Od /I ".." /I "%VOTAGUS_ROOT%app/" /I "%VOTAGUS_ROOT%app/thirdparty/include" /I "%VOTAGUS_ROOT%app/thirdparty/appseed" /I "%VOTAGUS_ROOT%app/appseedcore" /I "%VOTAGUS_ROOT%app/nodeapp/platform" /I "%VOTAGUS_ROOT%app/appseed" /I "%VOTAGUS_ROOT%app/appseedcore/include/win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_NETNODESCRIPT_DLL" /D "_WINDLL" /D "_MBCS" /FD /EHa /RTC1 /MDd /Yu"stdafx.h" /Fp"%VOTAGUS_ROOT%time/intermediate/Debug/netnodescript\netnodescript.pch" /Fo"%VOTAGUS_ROOT%time/intermediate/Debug/netnodescript\\" /Fd"%VOTAGUS_ROOT%time/intermediate/Debug/netnodescript\vc90.pdb" /W3 /nologo /c /ZI /TP /errorReport:prompt  -Zm184

link /OUT:"%VOTAGUS_ROOT%stage/Debug\netnodescript.dll" /INCREMENTAL /NOLOGO /LIBPATH:"%VOTAGUS_ROOT%time/library/Debug/" /LIBPATH:"%VOTAGUS_ROOT%app/thirdparty/library" /DLL /MANIFEST:NO /DEF:"./netnode_script.def" /DEBUG /PDB:"c:\votagus\netnode\stage\Debug\netnodescript.pdb" /SUBSYSTEM:WINDOWS /DYNAMICBASE:NO /NXCOMPAT /IMPLIB:"%VOTAGUS_ROOT%time/library/Debug/netnodescript.lib" /MACHINE:X86 /ERRORREPORT:PROMPT freeimage.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib "..\..\..\time\library\debug\ca2api024_00084.lib"
