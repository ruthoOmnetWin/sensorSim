#
# OMNeT++/OMNEST Makefile for ApplicationClusteringImplementations
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -I../../MiXiM/src/base/modules -I../../SensorTechnology/src/SensorNode/Processor -I../../MiXiM/src -I../../MiXiM/src/base/utils -I../../MiXiM/src/modules/power/battery -I../../MiXiM/src/base -I../../MiXiM/src/inet_stub/mobility/models -I../../MiXiM/src/modules/phy -I../../SensorTechnology/src/SensorNode -I../../MiXiM/src/inet_stub/mobility -I../../SensorTechnology/src/ExtendedMessage -I../../MiXiM/src/base/connectionManager -I../../MiXiM/src/inet_stub/base -I../../SensorTechnology/src/SimpleSensorData -I../../SensorTechnology/src -I../../MiXiM/src/modules/netw -I../../MiXiM/src/inet_stub/networklayer/common -I../../MiXiM/src/modules/utility -I../../MiXiM/src/base/phyLayer -I../../MiXiM/src/inet_stub/util -I../../MiXiM/src/modules/analogueModel -I../../MiXiM/src/modules/messages -I../../MiXiM/src/inet_stub/linklayer/contract -I../../MiXiM/src/base/messages -I../../SensorTechnology/src/SensorNode/Memory -I../../MiXiM/src/modules -L../../MiXiM/out/$$\(CONFIGNAME\)/src -L../../SensorTechnology/out/$$\(CONFIGNAME\)/src -lmixim -lSensorTechnology -DMIXIM_INET=1 -KMIXIM_PROJ=../../MiXiM -KSENSORTECHNOLOGY_PROJ=../../SensorTechnology
#

# Name of target to be created (-o option)
TARGET = ApplicationClusteringImplementations$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../../MiXiM/src/base/modules \
    -I../../SensorTechnology/src/SensorNode/Processor \
    -I../../MiXiM/src \
    -I../../MiXiM/src/base/utils \
    -I../../MiXiM/src/modules/power/battery \
    -I../../MiXiM/src/base \
    -I../../MiXiM/src/inet_stub/mobility/models \
    -I../../MiXiM/src/modules/phy \
    -I../../SensorTechnology/src/SensorNode \
    -I../../MiXiM/src/inet_stub/mobility \
    -I../../SensorTechnology/src/ExtendedMessage \
    -I../../MiXiM/src/base/connectionManager \
    -I../../MiXiM/src/inet_stub/base \
    -I../../SensorTechnology/src/SimpleSensorData \
    -I../../SensorTechnology/src \
    -I../../MiXiM/src/modules/netw \
    -I../../MiXiM/src/inet_stub/networklayer/common \
    -I../../MiXiM/src/modules/utility \
    -I../../MiXiM/src/base/phyLayer \
    -I../../MiXiM/src/inet_stub/util \
    -I../../MiXiM/src/modules/analogueModel \
    -I../../MiXiM/src/modules/messages \
    -I../../MiXiM/src/inet_stub/linklayer/contract \
    -I../../MiXiM/src/base/messages \
    -I../../SensorTechnology/src/SensorNode/Memory \
    -I../../MiXiM/src/modules \
    -I. \
    -Idata \
    -Iresults

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../MiXiM/out/$(CONFIGNAME)/src -L../../SensorTechnology/out/$(CONFIGNAME)/src  -lmixim -lSensorTechnology
LIBS += -Wl,-rpath,`abspath ../../MiXiM/out/$(CONFIGNAME)/src` -Wl,-rpath,`abspath ../../SensorTechnology/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = $O/CustomWiseRoute.o $O/ApplicationClusteringImplementations.o

# Message files
MSGFILES =

# Other makefile variables (-K)
MIXIM_PROJ=../../MiXiM
SENSORTECHNOLOGY_PROJ=../../SensorTechnology

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
	$(Q)-rm -f ApplicationClusteringImplementations ApplicationClusteringImplementations.exe libApplicationClusteringImplementations.so libApplicationClusteringImplementations.a libApplicationClusteringImplementations.dll libApplicationClusteringImplementations.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f data/*_m.cc data/*_m.h
	$(Q)-rm -f results/*_m.cc results/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc data/*.cc results/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/ApplicationClusteringImplementations.o: ApplicationClusteringImplementations.cc \
	ApplicationClusteringImplementations.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/SensorNode.h
$O/CustomWiseRoute.o: CustomWiseRoute.cc \
	CustomWiseRoute.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/ArpInterface.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseNetwLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MacToNetwControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/NetwControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/messages/WiseRoutePkt_m.h \
	$(MIXIM_PROJ)/src/modules/netw/WiseRoute.h \
	$(MIXIM_PROJ)/src/modules/utility/Packet.h \
	$(MIXIM_PROJ)/src/modules/utility/SimTracer.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/SensorNode.h

