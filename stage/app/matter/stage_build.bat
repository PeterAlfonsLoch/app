call "%VS100COMNTOOLS%\..\..\VC\bin\vcvars32.bat"

VCExpress "T:\stage\app\seed\metaseed\all.sln" /build basis
VCExpress "T:\stage\app\seed\metaseed\all64.sln" /build basis


