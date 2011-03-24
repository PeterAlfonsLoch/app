call "%VS100COMNTOOLS%\..\..\VC\bin\vcvars32.bat"

VCExpress "V:\votagus\basis\app\ccvotagus\seed\ccvotagus_ca2_basis_spa.sln" /build Release
VCExpress "V:\votagus\basis\app\ccvotagus\seed\ccvotagus_ca2_basis_spa64.sln" /build Release
VCExpress "V:\votagus\basis\app\seed\metaseed\av.sln" /build basis
VCExpress "V:\votagus\basis\app\seed\metaseed\av64.sln" /build basis
VCExpress "V:\votagus\basis\app\seed\metaseed\all.sln" /build basis
VCExpress "V:\votagus\basis\app\seed\metaseed\all64.sln" /build basis


