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
	${OBJECTDIR}/_ext/583780700/c_os.o


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
	"${MAKE}"  -f nbproject/Makefile-Release.mk dist/Release/OracleSolarisStudio-Solaris-x86/lib_ca2c.so

dist/Release/OracleSolarisStudio-Solaris-x86/lib_ca2c.so: ${OBJECTFILES}
	${MKDIR} -p dist/Release/OracleSolarisStudio-Solaris-x86
	${LINK.c} -G -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lib_ca2c.so -KPIC -norunpath -h lib_ca2c.so ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/583780700/c_os.o: ../solaris/c_os.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.c) -fast -g -KPIC  -o ${OBJECTDIR}/_ext/583780700/c_os.o ../solaris/c_os.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/OracleSolarisStudio-Solaris-x86/lib_ca2c.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
