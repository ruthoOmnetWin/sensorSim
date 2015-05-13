#
# OMNeT++/OMNEST Makefile for SensorTechnology
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -I/home/rutho/BA/mixim-2.3/src/base/phyLayer -I/home/rutho/BA/mixim-2.3/src -I/home/rutho/BA/mixim-2.3/src/base -I/home/rutho/BA/mixim-2.3/src/inet_stub/mobility -I/home/rutho/BA/mixim-2.3/src/base/utils -I/home/rutho/BA/mixim-2.3/src/base/modules -I/home/rutho/BA/mixim-2.3/src/inet_stub/base -I/home/rutho/BA/mixim-2.3/src/modules/power/battery -I/home/rutho/BA/mixim-2.3/src/inet_stub/util -I/home/rutho/BA/mixim-2.3/src/inet_stub/linklayer/contract -I/home/rutho/BA/mixim-2.3/src/base/messages -I/home/rutho/BA/mixim-2.3/src/base/connectionManager -I/home/rutho/BA/mixim-2.3/src/inet_stub/mobility/models -I/home/rutho/BA/mixim-2.3/src/inet_stub/networklayer/common -L/home/rutho/BA/mixim-2.3/out/$$\(CONFIGNAME\)/src -lmixim -DMIXIM_INET=1 -KMIXIM_PROJ=/home/rutho/BA/mixim-2.3
#

# Name of target to be created (-o option)
TARGET = SensorTechnology$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I$(MIXIM_PROJ)/src/base/phyLayer \
    -I$(MIXIM_PROJ)/src \
    -I$(MIXIM_PROJ)/src/base \
    -I$(MIXIM_PROJ)/src/inet_stub/mobility \
    -I$(MIXIM_PROJ)/src/base/utils \
    -I$(MIXIM_PROJ)/src/base/modules \
    -I$(MIXIM_PROJ)/src/inet_stub/base \
    -I$(MIXIM_PROJ)/src/modules/power/battery \
    -I$(MIXIM_PROJ)/src/inet_stub/util \
    -I$(MIXIM_PROJ)/src/inet_stub/linklayer/contract \
    -I$(MIXIM_PROJ)/src/base/messages \
    -I$(MIXIM_PROJ)/src/base/connectionManager \
    -I$(MIXIM_PROJ)/src/inet_stub/mobility/models \
    -I$(MIXIM_PROJ)/src/inet_stub/networklayer/common \
    -I. \
    -Idoc \
    -Idoc/doxy \
    -Idoc/doxy/search \
    -Idoc/neddoc \
    -Iexamples \
    -Iexamples/AllNodes \
    -Iexamples/AllNodes/data \
    -Iexamples/AllNodes/results \
    -Iexamples/BasicExample \
    -Iexamples/BasicExample/data \
    -Iexamples/BasicExample/results \
    -Iexamples/SensorExample \
    -Iexamples/SensorExample/data \
    -Iexamples/SensorExample/results \
    -Iexamples/SleepOutOfSync \
    -Iexamples/SleepOutOfSync/data \
    -Iexamples/SleepOutOfSync/results \
    -Iexamples/SleepVsNoSleep \
    -Iexamples/SleepVsNoSleep/data \
    -Iexamples/SleepVsNoSleep/results \
    -Iexamples/TrafficGenExample \
    -Iexamples/TrafficGenExample/data \
    -Iexamples/TrafficGenExample/results \
    -Isrc \
    -Isrc/ExtendedMessage \
    -Isrc/SensorNetworkInterface \
    -Isrc/SensorNode \
    -Isrc/SensorNode/Memory \
    -Isrc/SensorNode/Processor \
    -Isrc/SensorNode/Sensor \
    -Isrc/SensorNode/Sensor/SensingUnit \
    -Isrc/SensorNode/Sensor/SignalConditioner \
    -Isrc/SensorNode/Sensor/SignalConverter \
    -Isrc/SensorNode/Sensor/Transducer \
    -Isrc/SimpleSensorData \
    -Isrc/StatisticsInterface \
    -Isrc/WorldModel

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L$(MIXIM_PROJ)/out/$(CONFIGNAME)/src  -lmixim
LIBS += -Wl,-rpath,`abspath $(MIXIM_PROJ)/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/src/SensorNode/BatteryAccess.o \
    $O/src/SensorNode/SensorNode.o \
    $O/src/SensorNode/Memory/Memory.o \
    $O/src/SensorNode/Processor/Processor.o \
    $O/src/SensorNode/Sensor/AbstractSensor.o \
    $O/src/SensorNode/Sensor/SensingUnit/AbstractSensingUnit.o \
    $O/src/SensorNode/Sensor/SignalConditioner/AbstractSignalConditioner.o \
    $O/src/SensorNode/Sensor/SignalConverter/AbstractSignalConverter.o \
    $O/src/SensorNode/Sensor/Transducer/AbstractTransducer.o \
    $O/src/SimpleSensorData/SimpleSensorData.o \
    $O/src/StatisticsInterface/StatisticsInterface.o \
    $O/src/WorldModel/CustomWorldUtility.o \
    $O/src/ExtendedMessage/ExtendedMessage_m.o

# Message files
MSGFILES = \
    src/ExtendedMessage/ExtendedMessage.msg

# Other makefile variables (-K)
MIXIM_PROJ=/home/rutho/BA/mixim-2.3

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) -DMIXIM_INET=1 $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f SensorTechnology SensorTechnology.exe libSensorTechnology.so libSensorTechnology.a libSensorTechnology.dll libSensorTechnology.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f doc/*_m.cc doc/*_m.h
	$(Q)-rm -f doc/doxy/*_m.cc doc/doxy/*_m.h
	$(Q)-rm -f doc/doxy/search/*_m.cc doc/doxy/search/*_m.h
	$(Q)-rm -f doc/neddoc/*_m.cc doc/neddoc/*_m.h
	$(Q)-rm -f examples/*_m.cc examples/*_m.h
	$(Q)-rm -f examples/AllNodes/*_m.cc examples/AllNodes/*_m.h
	$(Q)-rm -f examples/AllNodes/data/*_m.cc examples/AllNodes/data/*_m.h
	$(Q)-rm -f examples/AllNodes/results/*_m.cc examples/AllNodes/results/*_m.h
	$(Q)-rm -f examples/BasicExample/*_m.cc examples/BasicExample/*_m.h
	$(Q)-rm -f examples/BasicExample/data/*_m.cc examples/BasicExample/data/*_m.h
	$(Q)-rm -f examples/BasicExample/results/*_m.cc examples/BasicExample/results/*_m.h
	$(Q)-rm -f examples/SensorExample/*_m.cc examples/SensorExample/*_m.h
	$(Q)-rm -f examples/SensorExample/data/*_m.cc examples/SensorExample/data/*_m.h
	$(Q)-rm -f examples/SensorExample/results/*_m.cc examples/SensorExample/results/*_m.h
	$(Q)-rm -f examples/SleepOutOfSync/*_m.cc examples/SleepOutOfSync/*_m.h
	$(Q)-rm -f examples/SleepOutOfSync/data/*_m.cc examples/SleepOutOfSync/data/*_m.h
	$(Q)-rm -f examples/SleepOutOfSync/results/*_m.cc examples/SleepOutOfSync/results/*_m.h
	$(Q)-rm -f examples/SleepVsNoSleep/*_m.cc examples/SleepVsNoSleep/*_m.h
	$(Q)-rm -f examples/SleepVsNoSleep/data/*_m.cc examples/SleepVsNoSleep/data/*_m.h
	$(Q)-rm -f examples/SleepVsNoSleep/results/*_m.cc examples/SleepVsNoSleep/results/*_m.h
	$(Q)-rm -f examples/TrafficGenExample/*_m.cc examples/TrafficGenExample/*_m.h
	$(Q)-rm -f examples/TrafficGenExample/data/*_m.cc examples/TrafficGenExample/data/*_m.h
	$(Q)-rm -f examples/TrafficGenExample/results/*_m.cc examples/TrafficGenExample/results/*_m.h
	$(Q)-rm -f src/*_m.cc src/*_m.h
	$(Q)-rm -f src/ExtendedMessage/*_m.cc src/ExtendedMessage/*_m.h
	$(Q)-rm -f src/SensorNetworkInterface/*_m.cc src/SensorNetworkInterface/*_m.h
	$(Q)-rm -f src/SensorNode/*_m.cc src/SensorNode/*_m.h
	$(Q)-rm -f src/SensorNode/Memory/*_m.cc src/SensorNode/Memory/*_m.h
	$(Q)-rm -f src/SensorNode/Processor/*_m.cc src/SensorNode/Processor/*_m.h
	$(Q)-rm -f src/SensorNode/Sensor/*_m.cc src/SensorNode/Sensor/*_m.h
	$(Q)-rm -f src/SensorNode/Sensor/SensingUnit/*_m.cc src/SensorNode/Sensor/SensingUnit/*_m.h
	$(Q)-rm -f src/SensorNode/Sensor/SignalConditioner/*_m.cc src/SensorNode/Sensor/SignalConditioner/*_m.h
	$(Q)-rm -f src/SensorNode/Sensor/SignalConverter/*_m.cc src/SensorNode/Sensor/SignalConverter/*_m.h
	$(Q)-rm -f src/SensorNode/Sensor/Transducer/*_m.cc src/SensorNode/Sensor/Transducer/*_m.h
	$(Q)-rm -f src/SimpleSensorData/*_m.cc src/SimpleSensorData/*_m.h
	$(Q)-rm -f src/StatisticsInterface/*_m.cc src/StatisticsInterface/*_m.h
	$(Q)-rm -f src/WorldModel/*_m.cc src/WorldModel/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc doc/*.cc doc/doxy/*.cc doc/doxy/search/*.cc doc/neddoc/*.cc examples/*.cc examples/AllNodes/*.cc examples/AllNodes/data/*.cc examples/AllNodes/results/*.cc examples/BasicExample/*.cc examples/BasicExample/data/*.cc examples/BasicExample/results/*.cc examples/SensorExample/*.cc examples/SensorExample/data/*.cc examples/SensorExample/results/*.cc examples/SleepOutOfSync/*.cc examples/SleepOutOfSync/data/*.cc examples/SleepOutOfSync/results/*.cc examples/SleepVsNoSleep/*.cc examples/SleepVsNoSleep/data/*.cc examples/SleepVsNoSleep/results/*.cc examples/TrafficGenExample/*.cc examples/TrafficGenExample/data/*.cc examples/TrafficGenExample/results/*.cc src/*.cc src/ExtendedMessage/*.cc src/SensorNetworkInterface/*.cc src/SensorNode/*.cc src/SensorNode/Memory/*.cc src/SensorNode/Processor/*.cc src/SensorNode/Sensor/*.cc src/SensorNode/Sensor/SensingUnit/*.cc src/SensorNode/Sensor/SignalConditioner/*.cc src/SensorNode/Sensor/SignalConverter/*.cc src/SensorNode/Sensor/Transducer/*.cc src/SimpleSensorData/*.cc src/StatisticsInterface/*.cc src/WorldModel/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/src/ExtendedMessage/ExtendedMessage_m.o: src/ExtendedMessage/ExtendedMessage_m.cc \
	src/ExtendedMessage/ExtendedMessage_m.h
$O/src/SensorNode/BatteryAccess.o: src/SensorNode/BatteryAccess.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h \
	src/SensorNode/BatteryAccess.h \
	src/SensorNode/SensorNode.h
$O/src/SensorNode/SensorNode.o: src/SensorNode/SensorNode.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h \
	src/ExtendedMessage/ExtendedMessage_m.h \
	src/SensorNode/BatteryAccess.h \
	src/SensorNode/Processor/Processor.h \
	src/SensorNode/SensorNode.h
$O/src/SensorNode/Memory/Memory.o: src/SensorNode/Memory/Memory.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	src/SensorNode/BatteryAccess.h \
	src/SensorNode/Memory/Memory.h \
	src/SimpleSensorData/SimpleSensorData.h
$O/src/SensorNode/Processor/Processor.o: src/SensorNode/Processor/Processor.cc \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	src/SensorNode/BatteryAccess.h \
	src/SensorNode/Processor/Processor.h \
	src/SensorNode/SensorNode.h
$O/src/SensorNode/Sensor/AbstractSensor.o: src/SensorNode/Sensor/AbstractSensor.cc \
	src/SensorNode/Sensor/AbstractSensor.h
$O/src/SensorNode/Sensor/SensingUnit/AbstractSensingUnit.o: src/SensorNode/Sensor/SensingUnit/AbstractSensingUnit.cc \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	src/ExtendedMessage/ExtendedMessage_m.h \
	src/SensorNode/BatteryAccess.h \
	src/SensorNode/Sensor/SensingUnit/AbstractSensingUnit.h \
	src/SimpleSensorData/SimpleSensorData.h \
	src/StatisticsInterface/StatisticsInterface.h \
	src/WorldModel/CustomWorldUtility.h
$O/src/SensorNode/Sensor/SignalConditioner/AbstractSignalConditioner.o: src/SensorNode/Sensor/SignalConditioner/AbstractSignalConditioner.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	src/SensorNode/BatteryAccess.h \
	src/SensorNode/Sensor/SignalConditioner/AbstractSignalConditioner.h
$O/src/SensorNode/Sensor/SignalConverter/AbstractSignalConverter.o: src/SensorNode/Sensor/SignalConverter/AbstractSignalConverter.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	src/SensorNode/BatteryAccess.h \
	src/SensorNode/Sensor/SignalConverter/AbstractSignalConverter.h
$O/src/SensorNode/Sensor/Transducer/AbstractTransducer.o: src/SensorNode/Sensor/Transducer/AbstractTransducer.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	src/SensorNode/BatteryAccess.h \
	src/SensorNode/Sensor/Transducer/AbstractTransducer.h
$O/src/SimpleSensorData/SimpleSensorData.o: src/SimpleSensorData/SimpleSensorData.cc \
	src/SimpleSensorData/SimpleSensorData.h
$O/src/StatisticsInterface/StatisticsInterface.o: src/StatisticsInterface/StatisticsInterface.cc \
	src/ExtendedMessage/ExtendedMessage_m.h \
	src/StatisticsInterface/StatisticsInterface.h
$O/src/WorldModel/CustomWorldUtility.o: src/WorldModel/CustomWorldUtility.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	src/ExtendedMessage/ExtendedMessage_m.h \
	src/StatisticsInterface/StatisticsInterface.h \
	src/WorldModel/CustomWorldUtility.h

