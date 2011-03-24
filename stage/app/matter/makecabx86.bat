@echo off
mkdir ..\..\..\..\time\iexca2\
mkdir ..\..\..\..\time\iexca2\x86
del ..\..\..\..\time\iexca2\x86\iexca2.cab
IF NOT EXIST ..\..\..\..\time\iexca2\x86\iexca2.cab ECHO Deleted iexca2.cab
..\..\..\thirdparty\binary\cabarc N ..\..\..\..\time\iexca2\x86\iexca2.cab iexca2.inf ..\..\..\..\stage\x86\iexca2.dll
IF NOT EXIST ..\..\..\..\time\iexca2\x86\iexca2.cab ECHO ERROR WAS HAPPEND!!! 
IF EXIST ..\..\..\..\time\iexca2\x86\iexca2.cab ECHO Copy was successfully
..\..\..\thirdparty\binary\signtool sign /f "C:\cecyn1.at.hotmail.com\ccvotagus\cgcl\2011-02-ca2.p12" /p ca2514GrenLund ..\..\..\..\time\iexca2\x86\iexca2.cab