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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/spi/create_message.o \
	${OBJECTDIR}/src/spi/SocketSPI.o \
	${OBJECTDIR}/src/spi/SPI.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/spi/ConsoleSPI.o \
	${OBJECTDIR}/src/encoder/Encoder.o \
	${OBJECTDIR}/src/spi/commands/CommandResponse.o \
	${OBJECTDIR}/src/converters/PlainConverter.o \
	${OBJECTDIR}/src/spi/commands/SPICommand.o \
	${OBJECTDIR}/src/net/socketaddr_to_str.o \
	${OBJECTDIR}/src/net/create_server_socket.o \
	${OBJECTDIR}/src/engine/PersistentStatistics.o \
	${OBJECTDIR}/src/engine/Statistics.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ftk-5-networks-core-linux

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ftk-5-networks-core-linux: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ftk-5-networks-core-linux ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/spi/create_message.o: src/spi/create_message.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/spi
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/spi/create_message.o src/spi/create_message.cpp

${OBJECTDIR}/src/spi/SocketSPI.o: src/spi/SocketSPI.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/spi
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/spi/SocketSPI.o src/spi/SocketSPI.cpp

${OBJECTDIR}/src/spi/SPI.o: src/spi/SPI.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/spi
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/spi/SPI.o src/spi/SPI.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/spi/ConsoleSPI.o: src/spi/ConsoleSPI.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/spi
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/spi/ConsoleSPI.o src/spi/ConsoleSPI.cpp

${OBJECTDIR}/src/encoder/Encoder.o: src/encoder/Encoder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/encoder
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/encoder/Encoder.o src/encoder/Encoder.cpp

${OBJECTDIR}/src/spi/commands/CommandResponse.o: src/spi/commands/CommandResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/spi/commands
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/spi/commands/CommandResponse.o src/spi/commands/CommandResponse.cpp

${OBJECTDIR}/src/converters/PlainConverter.o: src/converters/PlainConverter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/converters
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/converters/PlainConverter.o src/converters/PlainConverter.cpp

${OBJECTDIR}/src/spi/commands/SPICommand.o: src/spi/commands/SPICommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/spi/commands
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/spi/commands/SPICommand.o src/spi/commands/SPICommand.cpp

${OBJECTDIR}/src/net/socketaddr_to_str.o: src/net/socketaddr_to_str.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/net
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/net/socketaddr_to_str.o src/net/socketaddr_to_str.cpp

${OBJECTDIR}/src/net/create_server_socket.o: src/net/create_server_socket.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/net
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/net/create_server_socket.o src/net/create_server_socket.cpp

${OBJECTDIR}/src/engine/PersistentStatistics.o: src/engine/PersistentStatistics.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/engine
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/engine/PersistentStatistics.o src/engine/PersistentStatistics.cpp

${OBJECTDIR}/src/engine/Statistics.o: src/engine/Statistics.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/engine
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/engine/Statistics.o src/engine/Statistics.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ftk-5-networks-core-linux

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
