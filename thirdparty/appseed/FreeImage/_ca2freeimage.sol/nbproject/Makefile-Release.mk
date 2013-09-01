#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=cc
CCC=CC
CXX=CC
FC=f95
AS=as

# Macros
CND_PLATFORM=OracleSolarisStudio-Solaris-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1491239072/CacheFile.o \
	${OBJECTDIR}/_ext/1491239072/PluginPCX.o \
	${OBJECTDIR}/_ext/1491239072/PluginTARGA.o \
	${OBJECTDIR}/_ext/1491239072/PluginPSD.o \
	${OBJECTDIR}/_ext/1491239072/PluginWBMP.o \
	${OBJECTDIR}/_ext/1491239072/PluginJ2K.o \
	${OBJECTDIR}/_ext/1491239072/PluginCUT.o \
	${OBJECTDIR}/_ext/1491239072/NNQuantizer.o \
	${OBJECTDIR}/_ext/1491239072/PluginEXR.o \
	${OBJECTDIR}/_ext/1491239072/ConversionFloat.o \
	${OBJECTDIR}/_ext/1491239072/PluginPCD.o \
	${OBJECTDIR}/_ext/1491239072/PluginKOALA.o \
	${OBJECTDIR}/_ext/1491239072/Plugin.o \
	${OBJECTDIR}/_ext/1491239072/PluginPICT.o \
	${OBJECTDIR}/_ext/1491239072/ToneMapping.o \
	${OBJECTDIR}/_ext/1491239072/FreeImageIO.o \
	${OBJECTDIR}/_ext/1491239072/Conversion16_565.o \
	${OBJECTDIR}/_ext/1491239072/PluginTIFF.o \
	${OBJECTDIR}/_ext/1491239072/PluginGIF.o \
	${OBJECTDIR}/_ext/1491239072/ConversionRGBF.o \
	${OBJECTDIR}/_ext/1491239072/PluginRAS.o \
	${OBJECTDIR}/_ext/1491239072/ZLibInterface.o \
	${OBJECTDIR}/_ext/1491239072/Conversion.o \
	${OBJECTDIR}/_ext/1491239072/tmoReinhard05.o \
	${OBJECTDIR}/_ext/1491239072/MultiPage.o \
	${OBJECTDIR}/_ext/1491239072/PluginJPEG.o \
	${OBJECTDIR}/_ext/1491239072/PluginPFM.o \
	${OBJECTDIR}/_ext/1491239072/tmoFattal02.o \
	${OBJECTDIR}/_ext/1491239072/ConversionUINT16.o \
	${OBJECTDIR}/_ext/1491239072/Conversion24.o \
	${OBJECTDIR}/_ext/1491239072/ColorLookup.o \
	${OBJECTDIR}/_ext/1491239072/TIFFLogLuv.o \
	${OBJECTDIR}/_ext/1491239072/ConversionType.o \
	${OBJECTDIR}/_ext/1491239072/PluginIFF.o \
	${OBJECTDIR}/_ext/1491239072/PluginG3.o \
	${OBJECTDIR}/_ext/1491239072/Conversion8.o \
	${OBJECTDIR}/_ext/1491239072/J2KHelper.o \
	${OBJECTDIR}/_ext/1491239072/MemoryIO.o \
	${OBJECTDIR}/_ext/1491239072/PluginJP2.o \
	${OBJECTDIR}/_ext/1491239072/PluginRAW.o \
	${OBJECTDIR}/_ext/1491239072/PSDParser.o \
	${OBJECTDIR}/_ext/1491239072/PluginHDR.o \
	${OBJECTDIR}/_ext/1491239072/PluginBMP.o \
	${OBJECTDIR}/_ext/1491239072/Halftoning.o \
	${OBJECTDIR}/_ext/1491239072/PluginXPM.o \
	${OBJECTDIR}/_ext/1491239072/FreeImage.o \
	${OBJECTDIR}/_ext/1491239072/Conversion32.o \
	${OBJECTDIR}/_ext/1491239072/PluginDDS.o \
	${OBJECTDIR}/_ext/1491239072/PixelAccess.o \
	${OBJECTDIR}/_ext/1491239072/WuQuantizer.o \
	${OBJECTDIR}/_ext/1491239072/FreeImageFramework.o \
	${OBJECTDIR}/_ext/1491239072/tmoColorConvert.o \
	${OBJECTDIR}/_ext/1491239072/PluginPNM.o \
	${OBJECTDIR}/_ext/1491239072/BitmapAccess.o \
	${OBJECTDIR}/_ext/1491239072/Conversion16_555.o \
	${OBJECTDIR}/_ext/1491239072/GetType.o \
	${OBJECTDIR}/_ext/1491239072/PluginMNG.o \
	${OBJECTDIR}/_ext/1491239072/Utilities.o \
	${OBJECTDIR}/_ext/1491239072/PluginXBM.o \
	${OBJECTDIR}/_ext/1491239072/Conversion4.o \
	${OBJECTDIR}/_ext/1491239072/PluginPNG.o \
	${OBJECTDIR}/_ext/1491239072/tmoDrago03.o \
	${OBJECTDIR}/_ext/1491239072/PluginSGI.o \
	${OBJECTDIR}/_ext/1491239072/PluginICO.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Release.mk dist/Release/OracleSolarisStudio-Solaris-x86/lib_ca2freeimage.so

dist/Release/OracleSolarisStudio-Solaris-x86/lib_ca2freeimage.so: ${OBJECTFILES}
	${MKDIR} -p dist/Release/OracleSolarisStudio-Solaris-x86
	${LINK.cc} -G -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lib_ca2freeimage.so -KPIC -norunpath -h lib_ca2freeimage.so ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1491239072/CacheFile.o: ../FreeImage/CacheFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/CacheFile.o ../FreeImage/CacheFile.cpp

${OBJECTDIR}/_ext/1491239072/PluginPCX.o: ../FreeImage/PluginPCX.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginPCX.o ../FreeImage/PluginPCX.cpp

${OBJECTDIR}/_ext/1491239072/PluginTARGA.o: ../FreeImage/PluginTARGA.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginTARGA.o ../FreeImage/PluginTARGA.cpp

${OBJECTDIR}/_ext/1491239072/PluginPSD.o: ../FreeImage/PluginPSD.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginPSD.o ../FreeImage/PluginPSD.cpp

${OBJECTDIR}/_ext/1491239072/PluginWBMP.o: ../FreeImage/PluginWBMP.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginWBMP.o ../FreeImage/PluginWBMP.cpp

${OBJECTDIR}/_ext/1491239072/PluginJ2K.o: ../FreeImage/PluginJ2K.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginJ2K.o ../FreeImage/PluginJ2K.cpp

${OBJECTDIR}/_ext/1491239072/PluginCUT.o: ../FreeImage/PluginCUT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginCUT.o ../FreeImage/PluginCUT.cpp

${OBJECTDIR}/_ext/1491239072/NNQuantizer.o: ../FreeImage/NNQuantizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/NNQuantizer.o ../FreeImage/NNQuantizer.cpp

${OBJECTDIR}/_ext/1491239072/PluginEXR.o: ../FreeImage/PluginEXR.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginEXR.o ../FreeImage/PluginEXR.cpp

${OBJECTDIR}/_ext/1491239072/ConversionFloat.o: ../FreeImage/ConversionFloat.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/ConversionFloat.o ../FreeImage/ConversionFloat.cpp

${OBJECTDIR}/_ext/1491239072/PluginPCD.o: ../FreeImage/PluginPCD.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginPCD.o ../FreeImage/PluginPCD.cpp

${OBJECTDIR}/_ext/1491239072/PluginKOALA.o: ../FreeImage/PluginKOALA.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginKOALA.o ../FreeImage/PluginKOALA.cpp

${OBJECTDIR}/_ext/1491239072/Plugin.o: ../FreeImage/Plugin.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/Plugin.o ../FreeImage/Plugin.cpp

${OBJECTDIR}/_ext/1491239072/PluginPICT.o: ../FreeImage/PluginPICT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginPICT.o ../FreeImage/PluginPICT.cpp

${OBJECTDIR}/_ext/1491239072/ToneMapping.o: ../FreeImage/ToneMapping.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/ToneMapping.o ../FreeImage/ToneMapping.cpp

${OBJECTDIR}/_ext/1491239072/FreeImageIO.o: ../FreeImage/FreeImageIO.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/FreeImageIO.o ../FreeImage/FreeImageIO.cpp

${OBJECTDIR}/_ext/1491239072/Conversion16_565.o: ../FreeImage/Conversion16_565.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/Conversion16_565.o ../FreeImage/Conversion16_565.cpp

${OBJECTDIR}/_ext/1491239072/PluginTIFF.o: ../FreeImage/PluginTIFF.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginTIFF.o ../FreeImage/PluginTIFF.cpp

${OBJECTDIR}/_ext/1491239072/PluginGIF.o: ../FreeImage/PluginGIF.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginGIF.o ../FreeImage/PluginGIF.cpp

${OBJECTDIR}/_ext/1491239072/ConversionRGBF.o: ../FreeImage/ConversionRGBF.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/ConversionRGBF.o ../FreeImage/ConversionRGBF.cpp

${OBJECTDIR}/_ext/1491239072/PluginRAS.o: ../FreeImage/PluginRAS.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginRAS.o ../FreeImage/PluginRAS.cpp

${OBJECTDIR}/_ext/1491239072/ZLibInterface.o: ../FreeImage/ZLibInterface.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/ZLibInterface.o ../FreeImage/ZLibInterface.cpp

${OBJECTDIR}/_ext/1491239072/Conversion.o: ../FreeImage/Conversion.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/Conversion.o ../FreeImage/Conversion.cpp

${OBJECTDIR}/_ext/1491239072/tmoReinhard05.o: ../FreeImage/tmoReinhard05.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/tmoReinhard05.o ../FreeImage/tmoReinhard05.cpp

${OBJECTDIR}/_ext/1491239072/MultiPage.o: ../FreeImage/MultiPage.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/MultiPage.o ../FreeImage/MultiPage.cpp

${OBJECTDIR}/_ext/1491239072/PluginJPEG.o: ../FreeImage/PluginJPEG.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginJPEG.o ../FreeImage/PluginJPEG.cpp

${OBJECTDIR}/_ext/1491239072/PluginPFM.o: ../FreeImage/PluginPFM.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginPFM.o ../FreeImage/PluginPFM.cpp

${OBJECTDIR}/_ext/1491239072/tmoFattal02.o: ../FreeImage/tmoFattal02.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/tmoFattal02.o ../FreeImage/tmoFattal02.cpp

${OBJECTDIR}/_ext/1491239072/ConversionUINT16.o: ../FreeImage/ConversionUINT16.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/ConversionUINT16.o ../FreeImage/ConversionUINT16.cpp

${OBJECTDIR}/_ext/1491239072/Conversion24.o: ../FreeImage/Conversion24.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/Conversion24.o ../FreeImage/Conversion24.cpp

${OBJECTDIR}/_ext/1491239072/ColorLookup.o: ../FreeImage/ColorLookup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/ColorLookup.o ../FreeImage/ColorLookup.cpp

${OBJECTDIR}/_ext/1491239072/TIFFLogLuv.o: ../FreeImage/TIFFLogLuv.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/TIFFLogLuv.o ../FreeImage/TIFFLogLuv.cpp

${OBJECTDIR}/_ext/1491239072/ConversionType.o: ../FreeImage/ConversionType.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/ConversionType.o ../FreeImage/ConversionType.cpp

${OBJECTDIR}/_ext/1491239072/PluginIFF.o: ../FreeImage/PluginIFF.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginIFF.o ../FreeImage/PluginIFF.cpp

${OBJECTDIR}/_ext/1491239072/PluginG3.o: ../FreeImage/PluginG3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginG3.o ../FreeImage/PluginG3.cpp

${OBJECTDIR}/_ext/1491239072/Conversion8.o: ../FreeImage/Conversion8.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/Conversion8.o ../FreeImage/Conversion8.cpp

${OBJECTDIR}/_ext/1491239072/J2KHelper.o: ../FreeImage/J2KHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/J2KHelper.o ../FreeImage/J2KHelper.cpp

${OBJECTDIR}/_ext/1491239072/MemoryIO.o: ../FreeImage/MemoryIO.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/MemoryIO.o ../FreeImage/MemoryIO.cpp

${OBJECTDIR}/_ext/1491239072/PluginJP2.o: ../FreeImage/PluginJP2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginJP2.o ../FreeImage/PluginJP2.cpp

${OBJECTDIR}/_ext/1491239072/PluginRAW.o: ../FreeImage/PluginRAW.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginRAW.o ../FreeImage/PluginRAW.cpp

${OBJECTDIR}/_ext/1491239072/PSDParser.o: ../FreeImage/PSDParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PSDParser.o ../FreeImage/PSDParser.cpp

${OBJECTDIR}/_ext/1491239072/PluginHDR.o: ../FreeImage/PluginHDR.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginHDR.o ../FreeImage/PluginHDR.cpp

${OBJECTDIR}/_ext/1491239072/PluginBMP.o: ../FreeImage/PluginBMP.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginBMP.o ../FreeImage/PluginBMP.cpp

${OBJECTDIR}/_ext/1491239072/Halftoning.o: ../FreeImage/Halftoning.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/Halftoning.o ../FreeImage/Halftoning.cpp

${OBJECTDIR}/_ext/1491239072/PluginXPM.o: ../FreeImage/PluginXPM.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginXPM.o ../FreeImage/PluginXPM.cpp

${OBJECTDIR}/_ext/1491239072/FreeImage.o: ../FreeImage/FreeImage.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/FreeImage.o ../FreeImage/FreeImage.cpp

${OBJECTDIR}/_ext/1491239072/Conversion32.o: ../FreeImage/Conversion32.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/Conversion32.o ../FreeImage/Conversion32.cpp

${OBJECTDIR}/_ext/1491239072/PluginDDS.o: ../FreeImage/PluginDDS.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginDDS.o ../FreeImage/PluginDDS.cpp

${OBJECTDIR}/_ext/1491239072/PixelAccess.o: ../FreeImage/PixelAccess.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PixelAccess.o ../FreeImage/PixelAccess.cpp

${OBJECTDIR}/_ext/1491239072/WuQuantizer.o: ../FreeImage/WuQuantizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/WuQuantizer.o ../FreeImage/WuQuantizer.cpp

${OBJECTDIR}/_ext/1491239072/FreeImageFramework.o: ../FreeImage/FreeImageFramework.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/FreeImageFramework.o ../FreeImage/FreeImageFramework.cpp

${OBJECTDIR}/_ext/1491239072/tmoColorConvert.o: ../FreeImage/tmoColorConvert.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/tmoColorConvert.o ../FreeImage/tmoColorConvert.cpp

${OBJECTDIR}/_ext/1491239072/PluginPNM.o: ../FreeImage/PluginPNM.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginPNM.o ../FreeImage/PluginPNM.cpp

${OBJECTDIR}/_ext/1491239072/BitmapAccess.o: ../FreeImage/BitmapAccess.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/BitmapAccess.o ../FreeImage/BitmapAccess.cpp

${OBJECTDIR}/_ext/1491239072/Conversion16_555.o: ../FreeImage/Conversion16_555.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/Conversion16_555.o ../FreeImage/Conversion16_555.cpp

${OBJECTDIR}/_ext/1491239072/GetType.o: ../FreeImage/GetType.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/GetType.o ../FreeImage/GetType.cpp

${OBJECTDIR}/_ext/1491239072/PluginMNG.o: ../FreeImage/PluginMNG.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginMNG.o ../FreeImage/PluginMNG.cpp

${OBJECTDIR}/_ext/1491239072/Utilities.o: ../FreeImage/Utilities.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/Utilities.o ../FreeImage/Utilities.cpp

${OBJECTDIR}/_ext/1491239072/PluginXBM.o: ../FreeImage/PluginXBM.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginXBM.o ../FreeImage/PluginXBM.cpp

${OBJECTDIR}/_ext/1491239072/Conversion4.o: ../FreeImage/Conversion4.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/Conversion4.o ../FreeImage/Conversion4.cpp

${OBJECTDIR}/_ext/1491239072/PluginPNG.o: ../FreeImage/PluginPNG.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginPNG.o ../FreeImage/PluginPNG.cpp

${OBJECTDIR}/_ext/1491239072/tmoDrago03.o: ../FreeImage/tmoDrago03.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/tmoDrago03.o ../FreeImage/tmoDrago03.cpp

${OBJECTDIR}/_ext/1491239072/PluginSGI.o: ../FreeImage/PluginSGI.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginSGI.o ../FreeImage/PluginSGI.cpp

${OBJECTDIR}/_ext/1491239072/PluginICO.o: ../FreeImage/PluginICO.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1491239072
	$(COMPILE.cc) -fast -g0 -I../../../../.. -I../.. -I../../../../appseed -I../../../include -I.. -KPIC  -o ${OBJECTDIR}/_ext/1491239072/PluginICO.o ../FreeImage/PluginICO.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/OracleSolarisStudio-Solaris-x86/lib_ca2freeimage.so
	${CCADMIN} -clean

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
