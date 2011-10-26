call "%VS100COMNTOOLS%\..\..\VC\bin\vcvars32.bat"

VCExpress "T:\stage\app\seed\metaseed\stage_all.sln" /build basis
VCExpress "T:\stage\app\seed\metaseed\stage_all64.sln" /build basis


