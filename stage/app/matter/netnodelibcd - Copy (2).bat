call "%VS_VARS%"

cd "%VOTAGUS_ROOT%appseed\ca2\fontopus\net\ds\common\netnode\"

cl /Zm184 /Od /I "%VOTAGUS_ROOT%netseed/ca2/fontopus/net/ds/ca2/include/" /I "%VOTAGUS_ROOT%netseed/ca2/fontopus/net/ds/ca2/library/" /I "%VOTAGUS_ROOT%appseed/ca2/fontopus/net/ds/common/netnodelibrary/" /I "%VOTAGUS_ROOT%appseed/ca2/fontopus/app/source/main/" /I "%VOTAGUS_ROOT%appseedcore/ca2core/fontopus/app/source/main" /I "%VOTAGUS_ROOT%appseed/ca2/fontopus/app/source/main/netnode/" /I "%VOTAGUS_ROOT%node/app/platform" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_NETNODELIBRARY_DLL" /D "_WINDLL" /D "_MBCS" /Gm /EHa /RTC1 /MDd /Yu"stdafx.h" /Fp"%VOTAGUS_ROOT%time/ca2/fontopus/app/main/build/intermediate/Debug/netnodelibrary/netnodelibrary.pch" /Fo"%VOTAGUS_ROOT%time/ca2/fontopus/app/main/build/intermediate/Debug/netnodelibrary/%ITEM_DIR%" /Fd"%VOTAGUS_ROOT%time/ca2/fontopus/app/main/build/intermediate/Debug/netnodelibrary/vc90.pdb" /W3 /nologo /c /Zi /TP /errorReport:prompt "%VOTAGUS_ROOT%time\ca2\fontopus\net\ds\common\netnode\%ITEM_NAME%.cpp" > "%VOTAGUS_ROOT%time\ca2\fontopus\net\ds\common\netnode\%ITEM_NAME%-compile-log.txt"

