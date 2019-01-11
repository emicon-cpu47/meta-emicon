# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))
WRVX_COMPBASE := $(subst \,/,$(WRVX_COMPBASE))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = PPC604gnu
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := C:/WindRiver/6.7/workspace
PRJ_ROOT_DIR := D:/temp/AUTO/CodesysSpV3/Templates/SysGraphicFBCstAdaption



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = ppc
CPU = PPC604
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=604 -mstrict-align -fno-implicit-fp
VSB_DIR = $(WIND_BASE)/target/lib
VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif


#Project Targets
PROJECT_TARGETS = SysGraphicFBCstAdaption/$(MODE_DIR)/SysGraphicFBCstAdaption.out


#Rules

# SysGraphicFBCstAdaption
ifeq ($(DEBUG_MODE),1)
SysGraphicFBCstAdaption/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
SysGraphicFBCstAdaption/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
SysGraphicFBCstAdaption/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
SysGraphicFBCstAdaption/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
SysGraphicFBCstAdaption/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
SysGraphicFBCstAdaption/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
SysGraphicFBCstAdaption/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
SysGraphicFBCstAdaption/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
SysGraphicFBCstAdaption/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
SysGraphicFBCstAdaption/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
SysGraphicFBCstAdaption/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
SysGraphicFBCstAdaption/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
SysGraphicFBCstAdaption/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip -ID:/temp/AUTO/CodesysSpV3/Components -ID:/temp/AUTO/CodesysSpV3/Platforms/VxWorks -ID:/temp/AUTO/CodesysSpV3/Platforms/VxWorks/Sys 
SysGraphicFBCstAdaption/$(MODE_DIR)/% : IDE_LIBRARIES = 
SysGraphicFBCstAdaption/$(MODE_DIR)/% : PROJECT_TYPE = DKM
SysGraphicFBCstAdaption/$(MODE_DIR)/% : DEFINES = -DMIXED_LINK
SysGraphicFBCstAdaption/$(MODE_DIR)/% : EXPAND_DBG = 0
SysGraphicFBCstAdaption/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
SysGraphicFBCstAdaption/$(MODE_DIR)/% : CPU = PPC604
SysGraphicFBCstAdaption/$(MODE_DIR)/% : TOOL_FAMILY = gnu
SysGraphicFBCstAdaption/$(MODE_DIR)/% : TOOL = gnu
SysGraphicFBCstAdaption/$(MODE_DIR)/% : TOOL_PATH = 
SysGraphicFBCstAdaption/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=604 -mstrict-align -fno-implicit-fp
SysGraphicFBCstAdaption/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
SysGraphicFBCstAdaption/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
SysGraphicFBCstAdaption/$(MODE_DIR)/% : LIBPATH = 
SysGraphicFBCstAdaption/$(MODE_DIR)/% : LIBS = 
SysGraphicFBCstAdaption/$(MODE_DIR)/% : OBJ_DIR := SysGraphicFBCstAdaption/$(MODE_DIR)

SysGraphicFBCstAdaption/$(MODE_DIR)/Objects/SysGraphicFBCstAdaption.o : $(PRJ_ROOT_DIR)/SysGraphicFBCstAdaption.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall   -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


OBJECTS_SysGraphicFBCstAdaption = SysGraphicFBCstAdaption/$(MODE_DIR)/Objects/SysGraphicFBCstAdaption.o

SysGraphicFBCstAdaption/$(MODE_DIR)/SysGraphicFBCstAdaption.out : $(OBJECTS_SysGraphicFBCstAdaption)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmppc $(OBJECTS_SysGraphicFBCstAdaption) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall  $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc -r -nostdlib -Wl,-X -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_SysGraphicFBCstAdaption) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

SysGraphicFBCstAdaption/$(MODE_DIR)/SysGraphicFBCstAdaption_compile_file : $(FILE) ;

_clean :: SysGraphicFBCstAdaption/$(MODE_DIR)/SysGraphicFBCstAdaption_clean

SysGraphicFBCstAdaption/$(MODE_DIR)/SysGraphicFBCstAdaption_clean : 
	$(TRACE_FLAG)if [ -d "SysGraphicFBCstAdaption" ]; then cd "SysGraphicFBCstAdaption"; rm -rf $(MODE_DIR); fi

DEP_FILES := SysGraphicFBCstAdaption/$(MODE_DIR)/Objects/SysGraphicFBCstAdaption.d
-include $(DEP_FILES)


WIND_SCOPETOOLS_BASE := $(subst \,/,$(WIND_SCOPETOOLS_BASE))

clean_scopetools :
	$(TRACE_FLAG)rm -rf $(PRJ_ROOT_DIR)/.coveragescope/db

CLEAN_STEP := clean_scopetools


-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
