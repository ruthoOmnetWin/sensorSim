#
# OMNeT++/OMNEST Makefile for SensorTechnology
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -d src -L../MiXiM/out/$$\(CONFIGNAME\)/src -L./out/$$\(CONFIGNAME\)/src -lmixim -DMIXIM_INET=1 -KMIXIM_PROJ=../MiXiM
#

# Name of target to be created (-o option)
TARGET = SensorTechnology$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
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
    -Iexamples/TrafficGenExample/results

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../MiXiM/out/$(CONFIGNAME)/src -Lout/$(CONFIGNAME)/src  -lmixim
LIBS += -Wl,-rpath,`abspath ../MiXiM/out/$(CONFIGNAME)/src` -Wl,-rpath,`abspath out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS =

# Message files
MSGFILES =

# Other makefile variables (-K)
MIXIM_PROJ=../MiXiM

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

$O/$(TARGET): $(OBJS) submakedirs $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

submakedirs:  src_dir

.PHONY: all clean cleanall depend msgheaders  src
src: src_dir

src_dir:
	cd src && $(MAKE) all

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)
	$(Q)cd src && $(MAKE) msgheaders

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

	-$(Q)cd src && $(MAKE) clean

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc doc/*.cc doc/doxy/*.cc doc/doxy/search/*.cc doc/neddoc/*.cc examples/*.cc examples/AllNodes/*.cc examples/AllNodes/data/*.cc examples/AllNodes/results/*.cc examples/BasicExample/*.cc examples/BasicExample/data/*.cc examples/BasicExample/results/*.cc examples/SensorExample/*.cc examples/SensorExample/data/*.cc examples/SensorExample/results/*.cc examples/SleepOutOfSync/*.cc examples/SleepOutOfSync/data/*.cc examples/SleepOutOfSync/results/*.cc examples/SleepVsNoSleep/*.cc examples/SleepVsNoSleep/data/*.cc examples/SleepVsNoSleep/results/*.cc examples/TrafficGenExample/*.cc examples/TrafficGenExample/data/*.cc examples/TrafficGenExample/results/*.cc
	$(Q)-cd src && if [ -f Makefile ]; then $(MAKE) depend; fi

# DO NOT DELETE THIS LINE -- make depend depends on it.

