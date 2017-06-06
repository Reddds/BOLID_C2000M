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

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=i2c/i2c_ack.c i2c/i2c_clos.c i2c/i2c_dtrd.c i2c/i2c_eeap.c i2c/i2c_eebw.c i2c/i2c_eecr.c i2c/i2c_eepw.c i2c/i2c_eerr.c i2c/i2c_eesr.c i2c/i2c_gets.c i2c/i2c_idle.c i2c/i2c_nack.c i2c/i2c_open.c i2c/i2c_puts.c i2c/i2c_read.c i2c/i2c_rstr.c i2c/i2c_stop.c i2c/i2c_strt.c i2c/i2c_writ.c LCD/busyxlcd.c LCD/openxlcd.c LCD/putrxlcd.c LCD/putsxlcd.c LCD/readaddr.c LCD/readdata.c LCD/setcgram.c LCD/setddram.c LCD/wcmdxlcd.c LCD/writdata.c LCD/Print.c MODBUS/ModbusRtu.c MODBUS/Ports.c MODBUS/commonutils.c MODBUS/validation.c MODBUS/func20_file.c MODBUS/func43_device_id.c MODBUS/func100_system_command.c MODBUS/func1_5_15_coils.c MODBUS/func2_discrete_input.c MODBUS/func3_6_16_holding_registers.c MODBUS/func4_input_registers.c MODBUS/func101_user_command.c MODBUS/func102_device_status.c MODBUS/master.c Sections/SectionIdle.c Sections/SectionRooms.c Sections/SectionSettings.c configuration_bits.c interrupts.c main.c system.c user.c buttons.c ParametersController.c SettingsController.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/i2c/i2c_ack.p1 ${OBJECTDIR}/i2c/i2c_clos.p1 ${OBJECTDIR}/i2c/i2c_dtrd.p1 ${OBJECTDIR}/i2c/i2c_eeap.p1 ${OBJECTDIR}/i2c/i2c_eebw.p1 ${OBJECTDIR}/i2c/i2c_eecr.p1 ${OBJECTDIR}/i2c/i2c_eepw.p1 ${OBJECTDIR}/i2c/i2c_eerr.p1 ${OBJECTDIR}/i2c/i2c_eesr.p1 ${OBJECTDIR}/i2c/i2c_gets.p1 ${OBJECTDIR}/i2c/i2c_idle.p1 ${OBJECTDIR}/i2c/i2c_nack.p1 ${OBJECTDIR}/i2c/i2c_open.p1 ${OBJECTDIR}/i2c/i2c_puts.p1 ${OBJECTDIR}/i2c/i2c_read.p1 ${OBJECTDIR}/i2c/i2c_rstr.p1 ${OBJECTDIR}/i2c/i2c_stop.p1 ${OBJECTDIR}/i2c/i2c_strt.p1 ${OBJECTDIR}/i2c/i2c_writ.p1 ${OBJECTDIR}/LCD/busyxlcd.p1 ${OBJECTDIR}/LCD/openxlcd.p1 ${OBJECTDIR}/LCD/putrxlcd.p1 ${OBJECTDIR}/LCD/putsxlcd.p1 ${OBJECTDIR}/LCD/readaddr.p1 ${OBJECTDIR}/LCD/readdata.p1 ${OBJECTDIR}/LCD/setcgram.p1 ${OBJECTDIR}/LCD/setddram.p1 ${OBJECTDIR}/LCD/wcmdxlcd.p1 ${OBJECTDIR}/LCD/writdata.p1 ${OBJECTDIR}/LCD/Print.p1 ${OBJECTDIR}/MODBUS/ModbusRtu.p1 ${OBJECTDIR}/MODBUS/Ports.p1 ${OBJECTDIR}/MODBUS/commonutils.p1 ${OBJECTDIR}/MODBUS/validation.p1 ${OBJECTDIR}/MODBUS/func20_file.p1 ${OBJECTDIR}/MODBUS/func43_device_id.p1 ${OBJECTDIR}/MODBUS/func100_system_command.p1 ${OBJECTDIR}/MODBUS/func1_5_15_coils.p1 ${OBJECTDIR}/MODBUS/func2_discrete_input.p1 ${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1 ${OBJECTDIR}/MODBUS/func4_input_registers.p1 ${OBJECTDIR}/MODBUS/func101_user_command.p1 ${OBJECTDIR}/MODBUS/func102_device_status.p1 ${OBJECTDIR}/MODBUS/master.p1 ${OBJECTDIR}/Sections/SectionIdle.p1 ${OBJECTDIR}/Sections/SectionRooms.p1 ${OBJECTDIR}/Sections/SectionSettings.p1 ${OBJECTDIR}/configuration_bits.p1 ${OBJECTDIR}/interrupts.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/system.p1 ${OBJECTDIR}/user.p1 ${OBJECTDIR}/buttons.p1 ${OBJECTDIR}/ParametersController.p1 ${OBJECTDIR}/SettingsController.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/i2c/i2c_ack.p1.d ${OBJECTDIR}/i2c/i2c_clos.p1.d ${OBJECTDIR}/i2c/i2c_dtrd.p1.d ${OBJECTDIR}/i2c/i2c_eeap.p1.d ${OBJECTDIR}/i2c/i2c_eebw.p1.d ${OBJECTDIR}/i2c/i2c_eecr.p1.d ${OBJECTDIR}/i2c/i2c_eepw.p1.d ${OBJECTDIR}/i2c/i2c_eerr.p1.d ${OBJECTDIR}/i2c/i2c_eesr.p1.d ${OBJECTDIR}/i2c/i2c_gets.p1.d ${OBJECTDIR}/i2c/i2c_idle.p1.d ${OBJECTDIR}/i2c/i2c_nack.p1.d ${OBJECTDIR}/i2c/i2c_open.p1.d ${OBJECTDIR}/i2c/i2c_puts.p1.d ${OBJECTDIR}/i2c/i2c_read.p1.d ${OBJECTDIR}/i2c/i2c_rstr.p1.d ${OBJECTDIR}/i2c/i2c_stop.p1.d ${OBJECTDIR}/i2c/i2c_strt.p1.d ${OBJECTDIR}/i2c/i2c_writ.p1.d ${OBJECTDIR}/LCD/busyxlcd.p1.d ${OBJECTDIR}/LCD/openxlcd.p1.d ${OBJECTDIR}/LCD/putrxlcd.p1.d ${OBJECTDIR}/LCD/putsxlcd.p1.d ${OBJECTDIR}/LCD/readaddr.p1.d ${OBJECTDIR}/LCD/readdata.p1.d ${OBJECTDIR}/LCD/setcgram.p1.d ${OBJECTDIR}/LCD/setddram.p1.d ${OBJECTDIR}/LCD/wcmdxlcd.p1.d ${OBJECTDIR}/LCD/writdata.p1.d ${OBJECTDIR}/LCD/Print.p1.d ${OBJECTDIR}/MODBUS/ModbusRtu.p1.d ${OBJECTDIR}/MODBUS/Ports.p1.d ${OBJECTDIR}/MODBUS/commonutils.p1.d ${OBJECTDIR}/MODBUS/validation.p1.d ${OBJECTDIR}/MODBUS/func20_file.p1.d ${OBJECTDIR}/MODBUS/func43_device_id.p1.d ${OBJECTDIR}/MODBUS/func100_system_command.p1.d ${OBJECTDIR}/MODBUS/func1_5_15_coils.p1.d ${OBJECTDIR}/MODBUS/func2_discrete_input.p1.d ${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1.d ${OBJECTDIR}/MODBUS/func4_input_registers.p1.d ${OBJECTDIR}/MODBUS/func101_user_command.p1.d ${OBJECTDIR}/MODBUS/func102_device_status.p1.d ${OBJECTDIR}/MODBUS/master.p1.d ${OBJECTDIR}/Sections/SectionIdle.p1.d ${OBJECTDIR}/Sections/SectionRooms.p1.d ${OBJECTDIR}/Sections/SectionSettings.p1.d ${OBJECTDIR}/configuration_bits.p1.d ${OBJECTDIR}/interrupts.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/system.p1.d ${OBJECTDIR}/user.p1.d ${OBJECTDIR}/buttons.p1.d ${OBJECTDIR}/ParametersController.p1.d ${OBJECTDIR}/SettingsController.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/i2c/i2c_ack.p1 ${OBJECTDIR}/i2c/i2c_clos.p1 ${OBJECTDIR}/i2c/i2c_dtrd.p1 ${OBJECTDIR}/i2c/i2c_eeap.p1 ${OBJECTDIR}/i2c/i2c_eebw.p1 ${OBJECTDIR}/i2c/i2c_eecr.p1 ${OBJECTDIR}/i2c/i2c_eepw.p1 ${OBJECTDIR}/i2c/i2c_eerr.p1 ${OBJECTDIR}/i2c/i2c_eesr.p1 ${OBJECTDIR}/i2c/i2c_gets.p1 ${OBJECTDIR}/i2c/i2c_idle.p1 ${OBJECTDIR}/i2c/i2c_nack.p1 ${OBJECTDIR}/i2c/i2c_open.p1 ${OBJECTDIR}/i2c/i2c_puts.p1 ${OBJECTDIR}/i2c/i2c_read.p1 ${OBJECTDIR}/i2c/i2c_rstr.p1 ${OBJECTDIR}/i2c/i2c_stop.p1 ${OBJECTDIR}/i2c/i2c_strt.p1 ${OBJECTDIR}/i2c/i2c_writ.p1 ${OBJECTDIR}/LCD/busyxlcd.p1 ${OBJECTDIR}/LCD/openxlcd.p1 ${OBJECTDIR}/LCD/putrxlcd.p1 ${OBJECTDIR}/LCD/putsxlcd.p1 ${OBJECTDIR}/LCD/readaddr.p1 ${OBJECTDIR}/LCD/readdata.p1 ${OBJECTDIR}/LCD/setcgram.p1 ${OBJECTDIR}/LCD/setddram.p1 ${OBJECTDIR}/LCD/wcmdxlcd.p1 ${OBJECTDIR}/LCD/writdata.p1 ${OBJECTDIR}/LCD/Print.p1 ${OBJECTDIR}/MODBUS/ModbusRtu.p1 ${OBJECTDIR}/MODBUS/Ports.p1 ${OBJECTDIR}/MODBUS/commonutils.p1 ${OBJECTDIR}/MODBUS/validation.p1 ${OBJECTDIR}/MODBUS/func20_file.p1 ${OBJECTDIR}/MODBUS/func43_device_id.p1 ${OBJECTDIR}/MODBUS/func100_system_command.p1 ${OBJECTDIR}/MODBUS/func1_5_15_coils.p1 ${OBJECTDIR}/MODBUS/func2_discrete_input.p1 ${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1 ${OBJECTDIR}/MODBUS/func4_input_registers.p1 ${OBJECTDIR}/MODBUS/func101_user_command.p1 ${OBJECTDIR}/MODBUS/func102_device_status.p1 ${OBJECTDIR}/MODBUS/master.p1 ${OBJECTDIR}/Sections/SectionIdle.p1 ${OBJECTDIR}/Sections/SectionRooms.p1 ${OBJECTDIR}/Sections/SectionSettings.p1 ${OBJECTDIR}/configuration_bits.p1 ${OBJECTDIR}/interrupts.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/system.p1 ${OBJECTDIR}/user.p1 ${OBJECTDIR}/buttons.p1 ${OBJECTDIR}/ParametersController.p1 ${OBJECTDIR}/SettingsController.p1

# Source Files
SOURCEFILES=i2c/i2c_ack.c i2c/i2c_clos.c i2c/i2c_dtrd.c i2c/i2c_eeap.c i2c/i2c_eebw.c i2c/i2c_eecr.c i2c/i2c_eepw.c i2c/i2c_eerr.c i2c/i2c_eesr.c i2c/i2c_gets.c i2c/i2c_idle.c i2c/i2c_nack.c i2c/i2c_open.c i2c/i2c_puts.c i2c/i2c_read.c i2c/i2c_rstr.c i2c/i2c_stop.c i2c/i2c_strt.c i2c/i2c_writ.c LCD/busyxlcd.c LCD/openxlcd.c LCD/putrxlcd.c LCD/putsxlcd.c LCD/readaddr.c LCD/readdata.c LCD/setcgram.c LCD/setddram.c LCD/wcmdxlcd.c LCD/writdata.c LCD/Print.c MODBUS/ModbusRtu.c MODBUS/Ports.c MODBUS/commonutils.c MODBUS/validation.c MODBUS/func20_file.c MODBUS/func43_device_id.c MODBUS/func100_system_command.c MODBUS/func1_5_15_coils.c MODBUS/func2_discrete_input.c MODBUS/func3_6_16_holding_registers.c MODBUS/func4_input_registers.c MODBUS/func101_user_command.c MODBUS/func102_device_status.c MODBUS/master.c Sections/SectionIdle.c Sections/SectionRooms.c Sections/SectionSettings.c configuration_bits.c interrupts.c main.c system.c user.c buttons.c ParametersController.c SettingsController.c


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
${OBJECTDIR}/i2c/i2c_ack.p1: i2c/i2c_ack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_ack.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_ack.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_ack.p1  i2c/i2c_ack.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_ack.d ${OBJECTDIR}/i2c/i2c_ack.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_ack.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_clos.p1: i2c/i2c_clos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_clos.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_clos.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_clos.p1  i2c/i2c_clos.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_clos.d ${OBJECTDIR}/i2c/i2c_clos.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_clos.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_dtrd.p1: i2c/i2c_dtrd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_dtrd.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_dtrd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_dtrd.p1  i2c/i2c_dtrd.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_dtrd.d ${OBJECTDIR}/i2c/i2c_dtrd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_dtrd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_eeap.p1: i2c/i2c_eeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_eeap.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_eeap.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_eeap.p1  i2c/i2c_eeap.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_eeap.d ${OBJECTDIR}/i2c/i2c_eeap.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_eeap.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_eebw.p1: i2c/i2c_eebw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_eebw.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_eebw.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_eebw.p1  i2c/i2c_eebw.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_eebw.d ${OBJECTDIR}/i2c/i2c_eebw.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_eebw.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_eecr.p1: i2c/i2c_eecr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_eecr.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_eecr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_eecr.p1  i2c/i2c_eecr.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_eecr.d ${OBJECTDIR}/i2c/i2c_eecr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_eecr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_eepw.p1: i2c/i2c_eepw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_eepw.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_eepw.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_eepw.p1  i2c/i2c_eepw.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_eepw.d ${OBJECTDIR}/i2c/i2c_eepw.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_eepw.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_eerr.p1: i2c/i2c_eerr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_eerr.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_eerr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_eerr.p1  i2c/i2c_eerr.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_eerr.d ${OBJECTDIR}/i2c/i2c_eerr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_eerr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_eesr.p1: i2c/i2c_eesr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_eesr.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_eesr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_eesr.p1  i2c/i2c_eesr.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_eesr.d ${OBJECTDIR}/i2c/i2c_eesr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_eesr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_gets.p1: i2c/i2c_gets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_gets.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_gets.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_gets.p1  i2c/i2c_gets.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_gets.d ${OBJECTDIR}/i2c/i2c_gets.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_gets.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_idle.p1: i2c/i2c_idle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_idle.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_idle.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_idle.p1  i2c/i2c_idle.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_idle.d ${OBJECTDIR}/i2c/i2c_idle.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_idle.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_nack.p1: i2c/i2c_nack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_nack.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_nack.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_nack.p1  i2c/i2c_nack.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_nack.d ${OBJECTDIR}/i2c/i2c_nack.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_nack.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_open.p1: i2c/i2c_open.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_open.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_open.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_open.p1  i2c/i2c_open.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_open.d ${OBJECTDIR}/i2c/i2c_open.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_open.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_puts.p1: i2c/i2c_puts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_puts.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_puts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_puts.p1  i2c/i2c_puts.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_puts.d ${OBJECTDIR}/i2c/i2c_puts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_puts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_read.p1: i2c/i2c_read.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_read.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_read.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_read.p1  i2c/i2c_read.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_read.d ${OBJECTDIR}/i2c/i2c_read.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_read.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_rstr.p1: i2c/i2c_rstr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_rstr.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_rstr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_rstr.p1  i2c/i2c_rstr.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_rstr.d ${OBJECTDIR}/i2c/i2c_rstr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_rstr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_stop.p1: i2c/i2c_stop.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_stop.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_stop.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_stop.p1  i2c/i2c_stop.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_stop.d ${OBJECTDIR}/i2c/i2c_stop.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_stop.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_strt.p1: i2c/i2c_strt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_strt.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_strt.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_strt.p1  i2c/i2c_strt.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_strt.d ${OBJECTDIR}/i2c/i2c_strt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_strt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_writ.p1: i2c/i2c_writ.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_writ.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_writ.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_writ.p1  i2c/i2c_writ.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_writ.d ${OBJECTDIR}/i2c/i2c_writ.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_writ.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/busyxlcd.p1: LCD/busyxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/busyxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/busyxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/busyxlcd.p1  LCD/busyxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/busyxlcd.d ${OBJECTDIR}/LCD/busyxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/busyxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/openxlcd.p1: LCD/openxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/openxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/openxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/openxlcd.p1  LCD/openxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/openxlcd.d ${OBJECTDIR}/LCD/openxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/openxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/putrxlcd.p1: LCD/putrxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/putrxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/putrxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/putrxlcd.p1  LCD/putrxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/putrxlcd.d ${OBJECTDIR}/LCD/putrxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/putrxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/putsxlcd.p1: LCD/putsxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/putsxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/putsxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/putsxlcd.p1  LCD/putsxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/putsxlcd.d ${OBJECTDIR}/LCD/putsxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/putsxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/readaddr.p1: LCD/readaddr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/readaddr.p1.d 
	@${RM} ${OBJECTDIR}/LCD/readaddr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/readaddr.p1  LCD/readaddr.c 
	@-${MV} ${OBJECTDIR}/LCD/readaddr.d ${OBJECTDIR}/LCD/readaddr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/readaddr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/readdata.p1: LCD/readdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/readdata.p1.d 
	@${RM} ${OBJECTDIR}/LCD/readdata.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/readdata.p1  LCD/readdata.c 
	@-${MV} ${OBJECTDIR}/LCD/readdata.d ${OBJECTDIR}/LCD/readdata.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/readdata.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/setcgram.p1: LCD/setcgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/setcgram.p1.d 
	@${RM} ${OBJECTDIR}/LCD/setcgram.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/setcgram.p1  LCD/setcgram.c 
	@-${MV} ${OBJECTDIR}/LCD/setcgram.d ${OBJECTDIR}/LCD/setcgram.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/setcgram.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/setddram.p1: LCD/setddram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/setddram.p1.d 
	@${RM} ${OBJECTDIR}/LCD/setddram.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/setddram.p1  LCD/setddram.c 
	@-${MV} ${OBJECTDIR}/LCD/setddram.d ${OBJECTDIR}/LCD/setddram.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/setddram.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/wcmdxlcd.p1: LCD/wcmdxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/wcmdxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/wcmdxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/wcmdxlcd.p1  LCD/wcmdxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/wcmdxlcd.d ${OBJECTDIR}/LCD/wcmdxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/wcmdxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/writdata.p1: LCD/writdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/writdata.p1.d 
	@${RM} ${OBJECTDIR}/LCD/writdata.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/writdata.p1  LCD/writdata.c 
	@-${MV} ${OBJECTDIR}/LCD/writdata.d ${OBJECTDIR}/LCD/writdata.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/writdata.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/Print.p1: LCD/Print.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/Print.p1.d 
	@${RM} ${OBJECTDIR}/LCD/Print.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/Print.p1  LCD/Print.c 
	@-${MV} ${OBJECTDIR}/LCD/Print.d ${OBJECTDIR}/LCD/Print.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/Print.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/ModbusRtu.p1: MODBUS/ModbusRtu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/ModbusRtu.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/ModbusRtu.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/ModbusRtu.p1  MODBUS/ModbusRtu.c 
	@-${MV} ${OBJECTDIR}/MODBUS/ModbusRtu.d ${OBJECTDIR}/MODBUS/ModbusRtu.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/ModbusRtu.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/Ports.p1: MODBUS/Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/Ports.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/Ports.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/Ports.p1  MODBUS/Ports.c 
	@-${MV} ${OBJECTDIR}/MODBUS/Ports.d ${OBJECTDIR}/MODBUS/Ports.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/Ports.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/commonutils.p1: MODBUS/commonutils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/commonutils.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/commonutils.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/commonutils.p1  MODBUS/commonutils.c 
	@-${MV} ${OBJECTDIR}/MODBUS/commonutils.d ${OBJECTDIR}/MODBUS/commonutils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/commonutils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/validation.p1: MODBUS/validation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/validation.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/validation.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/validation.p1  MODBUS/validation.c 
	@-${MV} ${OBJECTDIR}/MODBUS/validation.d ${OBJECTDIR}/MODBUS/validation.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/validation.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func20_file.p1: MODBUS/func20_file.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func20_file.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func20_file.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func20_file.p1  MODBUS/func20_file.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func20_file.d ${OBJECTDIR}/MODBUS/func20_file.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func20_file.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func43_device_id.p1: MODBUS/func43_device_id.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func43_device_id.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func43_device_id.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func43_device_id.p1  MODBUS/func43_device_id.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func43_device_id.d ${OBJECTDIR}/MODBUS/func43_device_id.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func43_device_id.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func100_system_command.p1: MODBUS/func100_system_command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func100_system_command.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func100_system_command.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func100_system_command.p1  MODBUS/func100_system_command.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func100_system_command.d ${OBJECTDIR}/MODBUS/func100_system_command.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func100_system_command.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func1_5_15_coils.p1: MODBUS/func1_5_15_coils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func1_5_15_coils.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func1_5_15_coils.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func1_5_15_coils.p1  MODBUS/func1_5_15_coils.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func1_5_15_coils.d ${OBJECTDIR}/MODBUS/func1_5_15_coils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func1_5_15_coils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func2_discrete_input.p1: MODBUS/func2_discrete_input.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func2_discrete_input.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func2_discrete_input.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func2_discrete_input.p1  MODBUS/func2_discrete_input.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func2_discrete_input.d ${OBJECTDIR}/MODBUS/func2_discrete_input.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func2_discrete_input.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1: MODBUS/func3_6_16_holding_registers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1  MODBUS/func3_6_16_holding_registers.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.d ${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func4_input_registers.p1: MODBUS/func4_input_registers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func4_input_registers.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func4_input_registers.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func4_input_registers.p1  MODBUS/func4_input_registers.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func4_input_registers.d ${OBJECTDIR}/MODBUS/func4_input_registers.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func4_input_registers.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func101_user_command.p1: MODBUS/func101_user_command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func101_user_command.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func101_user_command.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func101_user_command.p1  MODBUS/func101_user_command.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func101_user_command.d ${OBJECTDIR}/MODBUS/func101_user_command.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func101_user_command.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func102_device_status.p1: MODBUS/func102_device_status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func102_device_status.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func102_device_status.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func102_device_status.p1  MODBUS/func102_device_status.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func102_device_status.d ${OBJECTDIR}/MODBUS/func102_device_status.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func102_device_status.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/master.p1: MODBUS/master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/master.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/master.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/master.p1  MODBUS/master.c 
	@-${MV} ${OBJECTDIR}/MODBUS/master.d ${OBJECTDIR}/MODBUS/master.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/master.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Sections/SectionIdle.p1: Sections/SectionIdle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sections" 
	@${RM} ${OBJECTDIR}/Sections/SectionIdle.p1.d 
	@${RM} ${OBJECTDIR}/Sections/SectionIdle.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Sections/SectionIdle.p1  Sections/SectionIdle.c 
	@-${MV} ${OBJECTDIR}/Sections/SectionIdle.d ${OBJECTDIR}/Sections/SectionIdle.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Sections/SectionIdle.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Sections/SectionRooms.p1: Sections/SectionRooms.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sections" 
	@${RM} ${OBJECTDIR}/Sections/SectionRooms.p1.d 
	@${RM} ${OBJECTDIR}/Sections/SectionRooms.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Sections/SectionRooms.p1  Sections/SectionRooms.c 
	@-${MV} ${OBJECTDIR}/Sections/SectionRooms.d ${OBJECTDIR}/Sections/SectionRooms.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Sections/SectionRooms.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Sections/SectionSettings.p1: Sections/SectionSettings.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sections" 
	@${RM} ${OBJECTDIR}/Sections/SectionSettings.p1.d 
	@${RM} ${OBJECTDIR}/Sections/SectionSettings.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Sections/SectionSettings.p1  Sections/SectionSettings.c 
	@-${MV} ${OBJECTDIR}/Sections/SectionSettings.d ${OBJECTDIR}/Sections/SectionSettings.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Sections/SectionSettings.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/configuration_bits.p1: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration_bits.p1.d 
	@${RM} ${OBJECTDIR}/configuration_bits.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/configuration_bits.p1  configuration_bits.c 
	@-${MV} ${OBJECTDIR}/configuration_bits.d ${OBJECTDIR}/configuration_bits.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/configuration_bits.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/interrupts.p1: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.p1.d 
	@${RM} ${OBJECTDIR}/interrupts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/interrupts.p1  interrupts.c 
	@-${MV} ${OBJECTDIR}/interrupts.d ${OBJECTDIR}/interrupts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/interrupts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main.p1  main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/system.p1: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.p1.d 
	@${RM} ${OBJECTDIR}/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/system.p1  system.c 
	@-${MV} ${OBJECTDIR}/system.d ${OBJECTDIR}/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/user.p1: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.p1.d 
	@${RM} ${OBJECTDIR}/user.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/user.p1  user.c 
	@-${MV} ${OBJECTDIR}/user.d ${OBJECTDIR}/user.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/user.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/buttons.p1: buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buttons.p1.d 
	@${RM} ${OBJECTDIR}/buttons.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/buttons.p1  buttons.c 
	@-${MV} ${OBJECTDIR}/buttons.d ${OBJECTDIR}/buttons.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/buttons.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ParametersController.p1: ParametersController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ParametersController.p1.d 
	@${RM} ${OBJECTDIR}/ParametersController.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ParametersController.p1  ParametersController.c 
	@-${MV} ${OBJECTDIR}/ParametersController.d ${OBJECTDIR}/ParametersController.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ParametersController.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SettingsController.p1: SettingsController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SettingsController.p1.d 
	@${RM} ${OBJECTDIR}/SettingsController.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SettingsController.p1  SettingsController.c 
	@-${MV} ${OBJECTDIR}/SettingsController.d ${OBJECTDIR}/SettingsController.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SettingsController.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/i2c/i2c_ack.p1: i2c/i2c_ack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_ack.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_ack.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_ack.p1  i2c/i2c_ack.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_ack.d ${OBJECTDIR}/i2c/i2c_ack.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_ack.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_clos.p1: i2c/i2c_clos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_clos.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_clos.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_clos.p1  i2c/i2c_clos.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_clos.d ${OBJECTDIR}/i2c/i2c_clos.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_clos.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_dtrd.p1: i2c/i2c_dtrd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_dtrd.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_dtrd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_dtrd.p1  i2c/i2c_dtrd.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_dtrd.d ${OBJECTDIR}/i2c/i2c_dtrd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_dtrd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_eeap.p1: i2c/i2c_eeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_eeap.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_eeap.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_eeap.p1  i2c/i2c_eeap.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_eeap.d ${OBJECTDIR}/i2c/i2c_eeap.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_eeap.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_eebw.p1: i2c/i2c_eebw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_eebw.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_eebw.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_eebw.p1  i2c/i2c_eebw.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_eebw.d ${OBJECTDIR}/i2c/i2c_eebw.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_eebw.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_eecr.p1: i2c/i2c_eecr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_eecr.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_eecr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_eecr.p1  i2c/i2c_eecr.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_eecr.d ${OBJECTDIR}/i2c/i2c_eecr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_eecr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_eepw.p1: i2c/i2c_eepw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_eepw.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_eepw.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_eepw.p1  i2c/i2c_eepw.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_eepw.d ${OBJECTDIR}/i2c/i2c_eepw.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_eepw.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_eerr.p1: i2c/i2c_eerr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_eerr.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_eerr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_eerr.p1  i2c/i2c_eerr.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_eerr.d ${OBJECTDIR}/i2c/i2c_eerr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_eerr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_eesr.p1: i2c/i2c_eesr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_eesr.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_eesr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_eesr.p1  i2c/i2c_eesr.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_eesr.d ${OBJECTDIR}/i2c/i2c_eesr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_eesr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_gets.p1: i2c/i2c_gets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_gets.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_gets.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_gets.p1  i2c/i2c_gets.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_gets.d ${OBJECTDIR}/i2c/i2c_gets.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_gets.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_idle.p1: i2c/i2c_idle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_idle.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_idle.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_idle.p1  i2c/i2c_idle.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_idle.d ${OBJECTDIR}/i2c/i2c_idle.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_idle.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_nack.p1: i2c/i2c_nack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_nack.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_nack.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_nack.p1  i2c/i2c_nack.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_nack.d ${OBJECTDIR}/i2c/i2c_nack.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_nack.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_open.p1: i2c/i2c_open.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_open.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_open.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_open.p1  i2c/i2c_open.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_open.d ${OBJECTDIR}/i2c/i2c_open.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_open.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_puts.p1: i2c/i2c_puts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_puts.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_puts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_puts.p1  i2c/i2c_puts.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_puts.d ${OBJECTDIR}/i2c/i2c_puts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_puts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_read.p1: i2c/i2c_read.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_read.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_read.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_read.p1  i2c/i2c_read.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_read.d ${OBJECTDIR}/i2c/i2c_read.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_read.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_rstr.p1: i2c/i2c_rstr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_rstr.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_rstr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_rstr.p1  i2c/i2c_rstr.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_rstr.d ${OBJECTDIR}/i2c/i2c_rstr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_rstr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_stop.p1: i2c/i2c_stop.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_stop.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_stop.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_stop.p1  i2c/i2c_stop.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_stop.d ${OBJECTDIR}/i2c/i2c_stop.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_stop.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_strt.p1: i2c/i2c_strt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_strt.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_strt.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_strt.p1  i2c/i2c_strt.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_strt.d ${OBJECTDIR}/i2c/i2c_strt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_strt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c/i2c_writ.p1: i2c/i2c_writ.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/i2c" 
	@${RM} ${OBJECTDIR}/i2c/i2c_writ.p1.d 
	@${RM} ${OBJECTDIR}/i2c/i2c_writ.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/i2c/i2c_writ.p1  i2c/i2c_writ.c 
	@-${MV} ${OBJECTDIR}/i2c/i2c_writ.d ${OBJECTDIR}/i2c/i2c_writ.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c/i2c_writ.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/busyxlcd.p1: LCD/busyxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/busyxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/busyxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/busyxlcd.p1  LCD/busyxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/busyxlcd.d ${OBJECTDIR}/LCD/busyxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/busyxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/openxlcd.p1: LCD/openxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/openxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/openxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/openxlcd.p1  LCD/openxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/openxlcd.d ${OBJECTDIR}/LCD/openxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/openxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/putrxlcd.p1: LCD/putrxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/putrxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/putrxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/putrxlcd.p1  LCD/putrxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/putrxlcd.d ${OBJECTDIR}/LCD/putrxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/putrxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/putsxlcd.p1: LCD/putsxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/putsxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/putsxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/putsxlcd.p1  LCD/putsxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/putsxlcd.d ${OBJECTDIR}/LCD/putsxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/putsxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/readaddr.p1: LCD/readaddr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/readaddr.p1.d 
	@${RM} ${OBJECTDIR}/LCD/readaddr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/readaddr.p1  LCD/readaddr.c 
	@-${MV} ${OBJECTDIR}/LCD/readaddr.d ${OBJECTDIR}/LCD/readaddr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/readaddr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/readdata.p1: LCD/readdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/readdata.p1.d 
	@${RM} ${OBJECTDIR}/LCD/readdata.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/readdata.p1  LCD/readdata.c 
	@-${MV} ${OBJECTDIR}/LCD/readdata.d ${OBJECTDIR}/LCD/readdata.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/readdata.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/setcgram.p1: LCD/setcgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/setcgram.p1.d 
	@${RM} ${OBJECTDIR}/LCD/setcgram.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/setcgram.p1  LCD/setcgram.c 
	@-${MV} ${OBJECTDIR}/LCD/setcgram.d ${OBJECTDIR}/LCD/setcgram.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/setcgram.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/setddram.p1: LCD/setddram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/setddram.p1.d 
	@${RM} ${OBJECTDIR}/LCD/setddram.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/setddram.p1  LCD/setddram.c 
	@-${MV} ${OBJECTDIR}/LCD/setddram.d ${OBJECTDIR}/LCD/setddram.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/setddram.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/wcmdxlcd.p1: LCD/wcmdxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/wcmdxlcd.p1.d 
	@${RM} ${OBJECTDIR}/LCD/wcmdxlcd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/wcmdxlcd.p1  LCD/wcmdxlcd.c 
	@-${MV} ${OBJECTDIR}/LCD/wcmdxlcd.d ${OBJECTDIR}/LCD/wcmdxlcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/wcmdxlcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/writdata.p1: LCD/writdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/writdata.p1.d 
	@${RM} ${OBJECTDIR}/LCD/writdata.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/writdata.p1  LCD/writdata.c 
	@-${MV} ${OBJECTDIR}/LCD/writdata.d ${OBJECTDIR}/LCD/writdata.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/writdata.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LCD/Print.p1: LCD/Print.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/LCD" 
	@${RM} ${OBJECTDIR}/LCD/Print.p1.d 
	@${RM} ${OBJECTDIR}/LCD/Print.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LCD/Print.p1  LCD/Print.c 
	@-${MV} ${OBJECTDIR}/LCD/Print.d ${OBJECTDIR}/LCD/Print.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LCD/Print.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/ModbusRtu.p1: MODBUS/ModbusRtu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/ModbusRtu.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/ModbusRtu.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/ModbusRtu.p1  MODBUS/ModbusRtu.c 
	@-${MV} ${OBJECTDIR}/MODBUS/ModbusRtu.d ${OBJECTDIR}/MODBUS/ModbusRtu.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/ModbusRtu.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/Ports.p1: MODBUS/Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/Ports.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/Ports.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/Ports.p1  MODBUS/Ports.c 
	@-${MV} ${OBJECTDIR}/MODBUS/Ports.d ${OBJECTDIR}/MODBUS/Ports.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/Ports.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/commonutils.p1: MODBUS/commonutils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/commonutils.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/commonutils.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/commonutils.p1  MODBUS/commonutils.c 
	@-${MV} ${OBJECTDIR}/MODBUS/commonutils.d ${OBJECTDIR}/MODBUS/commonutils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/commonutils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/validation.p1: MODBUS/validation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/validation.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/validation.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/validation.p1  MODBUS/validation.c 
	@-${MV} ${OBJECTDIR}/MODBUS/validation.d ${OBJECTDIR}/MODBUS/validation.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/validation.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func20_file.p1: MODBUS/func20_file.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func20_file.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func20_file.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func20_file.p1  MODBUS/func20_file.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func20_file.d ${OBJECTDIR}/MODBUS/func20_file.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func20_file.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func43_device_id.p1: MODBUS/func43_device_id.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func43_device_id.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func43_device_id.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func43_device_id.p1  MODBUS/func43_device_id.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func43_device_id.d ${OBJECTDIR}/MODBUS/func43_device_id.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func43_device_id.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func100_system_command.p1: MODBUS/func100_system_command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func100_system_command.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func100_system_command.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func100_system_command.p1  MODBUS/func100_system_command.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func100_system_command.d ${OBJECTDIR}/MODBUS/func100_system_command.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func100_system_command.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func1_5_15_coils.p1: MODBUS/func1_5_15_coils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func1_5_15_coils.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func1_5_15_coils.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func1_5_15_coils.p1  MODBUS/func1_5_15_coils.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func1_5_15_coils.d ${OBJECTDIR}/MODBUS/func1_5_15_coils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func1_5_15_coils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func2_discrete_input.p1: MODBUS/func2_discrete_input.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func2_discrete_input.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func2_discrete_input.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func2_discrete_input.p1  MODBUS/func2_discrete_input.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func2_discrete_input.d ${OBJECTDIR}/MODBUS/func2_discrete_input.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func2_discrete_input.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1: MODBUS/func3_6_16_holding_registers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1  MODBUS/func3_6_16_holding_registers.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.d ${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func3_6_16_holding_registers.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func4_input_registers.p1: MODBUS/func4_input_registers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func4_input_registers.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func4_input_registers.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func4_input_registers.p1  MODBUS/func4_input_registers.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func4_input_registers.d ${OBJECTDIR}/MODBUS/func4_input_registers.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func4_input_registers.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func101_user_command.p1: MODBUS/func101_user_command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func101_user_command.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func101_user_command.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func101_user_command.p1  MODBUS/func101_user_command.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func101_user_command.d ${OBJECTDIR}/MODBUS/func101_user_command.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func101_user_command.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/func102_device_status.p1: MODBUS/func102_device_status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/func102_device_status.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/func102_device_status.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/func102_device_status.p1  MODBUS/func102_device_status.c 
	@-${MV} ${OBJECTDIR}/MODBUS/func102_device_status.d ${OBJECTDIR}/MODBUS/func102_device_status.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/func102_device_status.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MODBUS/master.p1: MODBUS/master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/MODBUS" 
	@${RM} ${OBJECTDIR}/MODBUS/master.p1.d 
	@${RM} ${OBJECTDIR}/MODBUS/master.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MODBUS/master.p1  MODBUS/master.c 
	@-${MV} ${OBJECTDIR}/MODBUS/master.d ${OBJECTDIR}/MODBUS/master.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MODBUS/master.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Sections/SectionIdle.p1: Sections/SectionIdle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sections" 
	@${RM} ${OBJECTDIR}/Sections/SectionIdle.p1.d 
	@${RM} ${OBJECTDIR}/Sections/SectionIdle.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Sections/SectionIdle.p1  Sections/SectionIdle.c 
	@-${MV} ${OBJECTDIR}/Sections/SectionIdle.d ${OBJECTDIR}/Sections/SectionIdle.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Sections/SectionIdle.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Sections/SectionRooms.p1: Sections/SectionRooms.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sections" 
	@${RM} ${OBJECTDIR}/Sections/SectionRooms.p1.d 
	@${RM} ${OBJECTDIR}/Sections/SectionRooms.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Sections/SectionRooms.p1  Sections/SectionRooms.c 
	@-${MV} ${OBJECTDIR}/Sections/SectionRooms.d ${OBJECTDIR}/Sections/SectionRooms.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Sections/SectionRooms.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Sections/SectionSettings.p1: Sections/SectionSettings.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sections" 
	@${RM} ${OBJECTDIR}/Sections/SectionSettings.p1.d 
	@${RM} ${OBJECTDIR}/Sections/SectionSettings.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Sections/SectionSettings.p1  Sections/SectionSettings.c 
	@-${MV} ${OBJECTDIR}/Sections/SectionSettings.d ${OBJECTDIR}/Sections/SectionSettings.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Sections/SectionSettings.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/configuration_bits.p1: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration_bits.p1.d 
	@${RM} ${OBJECTDIR}/configuration_bits.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/configuration_bits.p1  configuration_bits.c 
	@-${MV} ${OBJECTDIR}/configuration_bits.d ${OBJECTDIR}/configuration_bits.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/configuration_bits.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/interrupts.p1: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.p1.d 
	@${RM} ${OBJECTDIR}/interrupts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/interrupts.p1  interrupts.c 
	@-${MV} ${OBJECTDIR}/interrupts.d ${OBJECTDIR}/interrupts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/interrupts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main.p1  main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/system.p1: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.p1.d 
	@${RM} ${OBJECTDIR}/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/system.p1  system.c 
	@-${MV} ${OBJECTDIR}/system.d ${OBJECTDIR}/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/user.p1: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.p1.d 
	@${RM} ${OBJECTDIR}/user.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/user.p1  user.c 
	@-${MV} ${OBJECTDIR}/user.d ${OBJECTDIR}/user.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/user.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/buttons.p1: buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buttons.p1.d 
	@${RM} ${OBJECTDIR}/buttons.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/buttons.p1  buttons.c 
	@-${MV} ${OBJECTDIR}/buttons.d ${OBJECTDIR}/buttons.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/buttons.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ParametersController.p1: ParametersController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ParametersController.p1.d 
	@${RM} ${OBJECTDIR}/ParametersController.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ParametersController.p1  ParametersController.c 
	@-${MV} ${OBJECTDIR}/ParametersController.d ${OBJECTDIR}/ParametersController.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ParametersController.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SettingsController.p1: SettingsController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SettingsController.p1.d 
	@${RM} ${OBJECTDIR}/SettingsController.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SettingsController.p1  SettingsController.c 
	@-${MV} ${OBJECTDIR}/SettingsController.d ${OBJECTDIR}/SettingsController.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SettingsController.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -DC2000M -DSERIAL_DEBUG -P -N255 --warn=-3 --asmlist -DXPRJ_XC8_18F6720=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/BOLID_C2000M.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
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
