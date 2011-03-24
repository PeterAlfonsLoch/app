call "%VS_VARS%"

cd "%VOTAGUS_ROOT%appseed\ca2\fontopus\net\ds\common\netnode\"

cl /Od /I ".." /I "%VOTAGUS_ROOT%app/" /I "%VOTAGUS_ROOT%app/thirdparty/include" /I "%VOTAGUS_ROOT%app/thirdparty/appseed" /I "%VOTAGUS_ROOT%app/appseedcore" /I "%VOTAGUS_ROOT%app/nodeapp/platform" /I "%VOTAGUS_ROOT%app/appseed" /I "%VOTAGUS_ROOT%app/appseedcore/include/win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_NETNODESCRIPT_DLL" /D "_WINDLL" /D "_MBCS" /FD /EHa /RTC1 /MDd /Yu"stdafx.h" /Fp"%VOTAGUS_ROOT%time/intermediate/Debug/netnodescript\netnodescript.pch" /Fo"%VOTAGUS_ROOT%time/intermediate/Debug/netnodescript\\" /Fd"%VOTAGUS_ROOT%time/intermediate/Debug/netnodescript\vc90.pdb" /W3 /nologo /c /ZI /TP /errorReport:prompt  -Zm184

