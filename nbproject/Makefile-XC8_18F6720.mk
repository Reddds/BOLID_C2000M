#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-XC8_18F6720.mk)" "nbproject/Makefile-local-XC8_18F6720.mk"
include nbproject/Makefile-local-XC8_18F6720.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=XC8_18F6720
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=--mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=LCD/busyxlcd.c LCD/openxlcd.c LCD/putrxlcd.c LCD/putsxlcd.c LCD/readaddr.c LCD/readdata.c LCD/setcgram.c LCD/setddram.c LCD/wcmdxlcd.c LCD/writdata.c LCD/Print.c Sections/SectionIdle.c Sections/SectionRooms.c Sections/SectionSettings.c configuration_bits.c interrupts.c main.c system.c user.c buttons.c ModbusRtu.c ParametersController.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/LCD/busyxlcd.p1 ${OBJECTDIR}/LCD/openxlcd.p1 ${OBJECTDIR}/LCD/putrxlcd.p1 ${OBJECTDIR}/LCD/putsxlcd.p1 ${OBJECTDIR}/LCD/readaddr.p1 ${OBJECTDIR}/LCD/readdata.p1 ${OBJECTDIR}/LCD/setcgram.p1 ${OBJECTDIR}/LCD/setddram.p1 ${OBJECTDIR}/LCD/wcmdxlcd.p1 ${OBJECTDIR}/LCD/writdata.p1 ${OBJECTDIR}/LCD/Print.p1 ${OBJECTDIR}/Sections/SectionIdle.p1 ${OBJECTDIR}/Sections/SectionRooms.p1 ${OBJECTDIR}/Sections/SectionSettings.p1 ${OBJECTDIR}/configuration_bits.p1 ${OBJECTDIR}/interrupts.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/system.p1 ${OBJECTDIR}/user.p1 ${OBJECTDIR}/buttons.p1 ${OBJECTDIR}/ModbusRtu.p1 ${OBJECTDIR}/ParametersController.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/LCD/busyxlcd.p1.d ${OBJECTDIR}/LCD/openxlcd.p1.d ${OBJECTDIR}/LCD/putrxlcd.p1.d ${OBJECTDIR}/LCD/putsxlcd.p1.d ${OBJECTDIR}/LCD/readaddr.p1.d ${OBJECTDIR}/LCD/readdata.p1.d ${OBJECTDIR}/LCD/setcgram.p1.d ${OBJECTDIR}/LCD/setddram.p1.d ${OBJECTDIR}/LCD/wcmdxlcd.p1.d ${OBJECTDIR}/LCD/writdata.p1.d ${OBJECTDIR}/LCD/Print.p1.d ${OBJECTDIR}/Sections/SectionIdle.p1.d ${OBJECTDIR}/Sections/SectionRooms.p1.d ${OBJECTDIR}/Sections/SectionSettings.p1.d ${OBJECTDIR}/configuration_bits.p1.d ${OBJECTDIR}/interrupts.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/system.p1.d ${OBJECTDIR}/user.p1.d ${OBJECTDIR}/buttons.p1.d ${OBJECTDIR}/ModbusRtu.p1.d ${OBJECTDIR}/ParametersController.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/LCD/busyxlcd.p1 ${OBJECTDIR}/LCD/openxlcd.p1 ${OBJECTDIR}/LCD/putrxlcd.p1 ${OBJECTDIR}/LCD/putsxlcd.p1 ${OBJECTDIR}/LCD/readaddr.p1 ${OBJECTDIR}/LCD/readdata.p1 ${OBJECTDIR}/LCD/setcgram.p1 ${OBJECTDIR}/LCD/setddram.p1 ${OBJECTDIR}/LCD/wcmdxlcd.p1 ${OBJECTDIR}/LCD/writdata.p1 ${OBJECTDIR}/LCD/Print.p1 ${OBJECTDIR}/Sections/SectionIdle.p1 ${OBJECTDIR}/Sections/SectionRooms.p1 ${OBJECTDIR}/Sections/SectionSettings.p1 ${OBJECTDIR}/configuration_bits.p1 ${OBJECTDIR}/interrupts.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/system.p1 ${OBJECTDIR}/user.p1 ${OBJECTDIR}/buttons.p1 ${OBJECTDIR}/ModbusRtu.p1 ${OBJECTDIR}/ParametersController.p1

# Source Files
SOURCEFILES=LCD/busyxlcd.c LCD/openxlcd.c LCD/putrxlcd.c LCD/putsxlcd.c LCD/readaddr.c LCD/readdata.c LCD/setcgram.c LCD/setddram.c LCD/wcmdxlcd.c LCD/writdata.c LCD/Print.c Sections/SectionIdle.c Sections/SectionRooms.c Sections/SectionSettings.c configuration_bits.c interrupts.c main.c system.c user.c buttons.c ModbusRtu.c ParametersController.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-XC8_18F6720.mk dist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F6720
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/LCD/busyxlcd.p1: LCD/busyxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/busyxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/busyxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/busyxlcd.p1  LCD/busyxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/busyxlcd.d ${OBJECTDIR}/LCD/busyxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/busyxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/openxlcd.p1: LCD/openxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/openxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/openxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/openxlcd.p1  LCD/openxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/openxlcd.d ${OBJECTDIR}/LCD/openxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/openxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/putrxlcd.p1: LCD/putrxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/putrxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/putrxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/putrxlcd.p1  LCD/putrxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/putrxlcd.d ${OBJECTDIR}/LCD/putrxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/putrxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/putsxlcd.p1: LCD/putsxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/putsxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/putsxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/putsxlcd.p1  LCD/putsxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/putsxlcd.d ${OBJECTDIR}/LCD/putsxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/putsxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/readaddr.p1: LCD/readaddr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/readaddr.p1.d 
	@${RM} ${OBJECTDIR}/LCD/readaddr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/readaddr.p1  LCD/readaddr.c 
	@-${MV} ${OBJECTDIR}/LCD/readaddr.d ${OBJECTDIR}/LCD/readaddr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/readaddr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/readdata.p1: LCD/readdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/readdata.p1.d 
	@${RM} ${OBJECTDIR}/LCD/readdata.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/readdata.p1  LCD/readdata.c 
	@-${MV} ${OBJECTDIR}/LCD/readdata.d ${OBJECTDIR}/LCD/readdata.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/readdata.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/setcgram.p1: LCD/setcgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/setcgram.p1.d 
	@${RM} ${OBJECTDIR}/LCD/setcgram.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/setcgram.p1  LCD/setcgram.c 
	@-${MV} ${OBJECTDIR}/LCD/setcgram.d ${OBJECTDIR}/LCD/setcgram.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/setcgram.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/setddram.p1: LCD/setddram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/setddram.p1.d 
	@${RM} ${OBJECTDIR}/LCD/setddram.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/setddram.p1  LCD/setddram.c 
	@-${MV} ${OBJECTDIR}/LCD/setddram.d ${OBJECTDIR}/LCD/setddram.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/setddram.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/wcmdxlcd.p1: LCD/wcmdxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/wcmdxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/wcmdxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/wcmdxlcd.p1  LCD/wcmdxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/wcmdxlcd.d ${OBJECTDIR}/LCD/wcmdxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/wcmdxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/writdata.p1: LCD/writdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/writdata.p1.d 
	@${RM} ${OBJECTDIR}/LCD/writdata.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/writdata.p1  LCD/writdata.c 
	@-${MV} ${OBJECTDIR}/LCD/writdata.d ${OBJECTDIR}/LCD/writdata.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/writdata.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/Print.p1: LCD/Print.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/Print.p1.d 
	@${RM} ${OBJECTDIR}/LCD/Print.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/Print.p1  LCD/Print.c 
	@-${MV} ${OBJECTDIR}/LCD/Print.d ${OBJECTDIR}/LCD/Print.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/Print.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Sections/SectionIdle.p1: Sections/SectionIdle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sections" 
	@${RM} ${OBJECTDIR}/Sections/SectionIdle.p1.d 
	@${RM} ${OBJECTDIR}/Sections/SectionIdle.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Sections/SectionIdle.p1  Sections/SectionIdle.c 
	@-${MV} ${OBJECTDIR}/Sections/SectionIdle.d ${OBJECTDIR}/Sections/SectionIdle.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Sections/SectionIdle.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Sections/SectionRooms.p1: Sections/SectionRooms.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sections" 
	@${RM} ${OBJECTDIR}/Sections/SectionRooms.p1.d 
	@${RM} ${OBJECTDIR}/Sections/SectionRooms.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Sections/SectionRooms.p1  Sections/SectionRooms.c 
	@-${MV} ${OBJECTDIR}/Sections/SectionRooms.d ${OBJECTDIR}/Sections/SectionRooms.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Sections/SectionRooms.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Sections/SectionSettings.p1: Sections/SectionSettings.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sections" 
	@${RM} ${OBJECTDIR}/Sections/SectionSettings.p1.d 
	@${RM} ${OBJECTDIR}/Sections/SectionSettings.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Sections/SectionSettings.p1  Sections/SectionSettings.c 
	@-${MV} ${OBJECTDIR}/Sections/SectionSettings.d ${OBJECTDIR}/Sections/SectionSettings.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Sections/SectionSettings.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/configuration_bits.p1: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration_bits.p1.d 
	@${RM} ${OBJECTDIR}/configuration_bits.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/configuration_bits.p1  configuration_bits.c 
	@-${MV} ${OBJECTDIR}/configuration_bits.d ${OBJECTDIR}/configuration_bits.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/configuration_bits.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/interrupts.p1: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.p1.d 
	@${RM} ${OBJECTDIR}/interrupts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/interrupts.p1  interrupts.c 
	@-${MV} ${OBJECTDIR}/interrupts.d ${OBJECTDIR}/interrupts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/interrupts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main.p1  main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/system.p1: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.p1.d 
	@${RM} ${OBJECTDIR}/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/system.p1  system.c 
	@-${MV} ${OBJECTDIR}/system.d ${OBJECTDIR}/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/user.p1: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.p1.d 
	@${RM} ${OBJECTDIR}/user.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/user.p1  user.c 
	@-${MV} ${OBJECTDIR}/user.d ${OBJECTDIR}/user.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/user.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/buttons.p1: buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buttons.p1.d 
	@${RM} ${OBJECTDIR}/buttons.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/buttons.p1  buttons.c 
	@-${MV} ${OBJECTDIR}/buttons.d ${OBJECTDIR}/buttons.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/buttons.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ModbusRtu.p1: ModbusRtu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ModbusRtu.p1.d 
	@${RM} ${OBJECTDIR}/ModbusRtu.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ModbusRtu.p1  ModbusRtu.c 
	@-${MV} ${OBJECTDIR}/ModbusRtu.d ${OBJECTDIR}/ModbusRtu.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ModbusRtu.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ParametersController.p1: ParametersController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ParametersController.p1.d 
	@${RM} ${OBJECTDIR}/ParametersController.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ParametersController.p1  ParametersController.c 
	@-${MV} ${OBJECTDIR}/ParametersController.d ${OBJECTDIR}/ParametersController.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ParametersController.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/LCD/busyxlcd.p1: LCD/busyxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/busyxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/busyxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/busyxlcd.p1  LCD/busyxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/busyxlcd.d ${OBJECTDIR}/LCD/busyxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/busyxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/openxlcd.p1: LCD/openxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/openxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/openxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/openxlcd.p1  LCD/openxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/openxlcd.d ${OBJECTDIR}/LCD/openxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/openxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/putrxlcd.p1: LCD/putrxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/putrxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/putrxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/putrxlcd.p1  LCD/putrxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/putrxlcd.d ${OBJECTDIR}/LCD/putrxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/putrxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/putsxlcd.p1: LCD/putsxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/putsxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/putsxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/putsxlcd.p1  LCD/putsxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/putsxlcd.d ${OBJECTDIR}/LCD/putsxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/putsxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/readaddr.p1: LCD/readaddr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/readaddr.p1.d 
	@${RM} ${OBJECTDIR}/LCD/readaddr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/readaddr.p1  LCD/readaddr.c 
	@-${MV} ${OBJECTDIR}/LCD/readaddr.d ${OBJECTDIR}/LCD/readaddr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/readaddr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/readdata.p1: LCD/readdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/readdata.p1.d 
	@${RM} ${OBJECTDIR}/LCD/readdata.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/readdata.p1  LCD/readdata.c 
	@-${MV} ${OBJECTDIR}/LCD/readdata.d ${OBJECTDIR}/LCD/readdata.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/readdata.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/setcgram.p1: LCD/setcgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/setcgram.p1.d 
	@${RM} ${OBJECTDIR}/LCD/setcgram.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/setcgram.p1  LCD/setcgram.c 
	@-${MV} ${OBJECTDIR}/LCD/setcgram.d ${OBJECTDIR}/LCD/setcgram.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/setcgram.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/setddram.p1: LCD/setddram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/setddram.p1.d 
	@${RM} ${OBJECTDIR}/LCD/setddram.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/setddram.p1  LCD/setddram.c 
	@-${MV} ${OBJECTDIR}/LCD/setddram.d ${OBJECTDIR}/LCD/setddram.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/setddram.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/wcmdxlcd.p1: LCD/wcmdxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/wcmdxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/wcmdxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/wcmdxlcd.p1  LCD/wcmdxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/wcmdxlcd.d ${OBJECTDIR}/LCD/wcmdxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/wcmdxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/writdata.p1: LCD/writdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/writdata.p1.d 
	@${RM} ${OBJECTDIR}/LCD/writdata.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/writdata.p1  LCD/writdata.c 
	@-${MV} ${OBJECTDIR}/LCD/writdata.d ${OBJECTDIR}/LCD/writdata.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/writdata.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/Print.p1: LCD/Print.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/Print.p1.d 
	@${RM} ${OBJECTDIR}/LCD/Print.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/Print.p1  LCD/Print.c 
	@-${MV} ${OBJECTDIR}/LCD/Print.d ${OBJECTDIR}/LCD/Print.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/Print.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Sections/SectionIdle.p1: Sections/SectionIdle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sections" 
	@${RM} ${OBJECTDIR}/Sections/SectionIdle.p1.d 
	@${RM} ${OBJECTDIR}/Sections/SectionIdle.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Sections/SectionIdle.p1  Sections/SectionIdle.c 
	@-${MV} ${OBJECTDIR}/Sections/SectionIdle.d ${OBJECTDIR}/Sections/SectionIdle.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Sections/SectionIdle.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Sections/SectionRooms.p1: Sections/SectionRooms.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sections" 
	@${RM} ${OBJECTDIR}/Sections/SectionRooms.p1.d 
	@${RM} ${OBJECTDIR}/Sections/SectionRooms.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Sections/SectionRooms.p1  Sections/SectionRooms.c 
	@-${MV} ${OBJECTDIR}/Sections/SectionRooms.d ${OBJECTDIR}/Sections/SectionRooms.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Sections/SectionRooms.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Sections/SectionSettings.p1: Sections/SectionSettings.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sections" 
	@${RM} ${OBJECTDIR}/Sections/SectionSettings.p1.d 
	@${RM} ${OBJECTDIR}/Sections/SectionSettings.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Sections/SectionSettings.p1  Sections/SectionSettings.c 
	@-${MV} ${OBJECTDIR}/Sections/SectionSettings.d ${OBJECTDIR}/Sections/SectionSettings.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Sections/SectionSettings.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/configuration_bits.p1: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration_bits.p1.d 
	@${RM} ${OBJECTDIR}/configuration_bits.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/configuration_bits.p1  configuration_bits.c 
	@-${MV} ${OBJECTDIR}/configuration_bits.d ${OBJECTDIR}/configuration_bits.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/configuration_bits.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/interrupts.p1: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.p1.d 
	@${RM} ${OBJECTDIR}/interrupts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/interrupts.p1  interrupts.c 
	@-${MV} ${OBJECTDIR}/interrupts.d ${OBJECTDIR}/interrupts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/interrupts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main.p1  main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/system.p1: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.p1.d 
	@${RM} ${OBJECTDIR}/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/system.p1  system.c 
	@-${MV} ${OBJECTDIR}/system.d ${OBJECTDIR}/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/user.p1: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.p1.d 
	@${RM} ${OBJECTDIR}/user.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/user.p1  user.c 
	@-${MV} ${OBJECTDIR}/user.d ${OBJECTDIR}/user.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/user.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/buttons.p1: buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buttons.p1.d 
	@${RM} ${OBJECTDIR}/buttons.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/buttons.p1  buttons.c 
	@-${MV} ${OBJECTDIR}/buttons.d ${OBJECTDIR}/buttons.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/buttons.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ModbusRtu.p1: ModbusRtu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ModbusRtu.p1.d 
	@${RM} ${OBJECTDIR}/ModbusRtu.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ModbusRtu.p1  ModbusRtu.c 
	@-${MV} ${OBJECTDIR}/ModbusRtu.d ${OBJECTDIR}/ModbusRtu.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ModbusRtu.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ParametersController.p1: ParametersController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ParametersController.p1.d 
	@${RM} ${OBJECTDIR}/ParametersController.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ParametersController.p1  ParametersController.c 
	@-${MV} ${OBJECTDIR}/ParametersController.d ${OBJECTDIR}/ParametersController.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ParametersController.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/XC8_18F6720
	${RM} -r dist/XC8_18F6720

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
