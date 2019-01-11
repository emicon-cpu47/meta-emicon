######################################################################################
######################################################################################
## Copyright:»··© 3S - Smart Software Solutions GmbH, Kempten                       ##
## Program: »···Linux dynamic linking makefile                                      ##
## Module: »····Makefile                                                            ##
## Version:»····0.1                                                                 ##
## Author:      3s-software. (PhB)                                                  ##
######################################################################################

#NOTE: firts do:
# export QNX_HOST=/customers/3s/qnx/toolchain/qnx650/host/linux/x86/
# export QNX_TARGET=/customers/3s/qnx/toolchain/qnx650/target/qnx6/

TARGET = CmpJitter
QNX_PATH = /customers/3s/qnx/toolchain/

INCLUDE = -I../ -I../../../Components -I../../../Platforms/Linux

CXX = $(QNX_PATH)/qnx650/host/linux/x86/usr/bin/qcc
# TRG_X86 | TRG_PPC | TRG_ARM | TRG_CORTEX
CXXFLAGS = -DTRG_X86

DEBFLAGS = -g
CXXFLAGS += -DCDECL= -DHANDLE_WIN32_PRAGMA -DDLL_DECL= -D_REENTRANT= -DHUGEPTR= 
CXXFLAGS += -O0 -Wall -Wno-unused
CXXFLAGS += $(INCLUDE)
CXXFLAGS += -DLINUX
CXXFLAGS += $(DEBFLAGS)
CXXFLAGS += -fPIC
CXXFLAGS += -Vgcc_ntox86
#LSFLAGS += $(QNX_PATH)/qnx650/target/qnx6/x86/usr/lib/libcache.a
#LSFLAGS += $(QNX_PATH)/qnx650/target/qnx6/x86/usr/lib/libpcap.a
LDFLAGS += -Vgcc_ntox86

MAJORVER = 0
MINORVER = 1
SONAME = lib$(TARGET).so.$(MAJORVER)
LIBNAME = $(SONAME).$(MINORVER)

SRC =  ../$(TARGET).c
OBJ = $(SRC:.c=.o)

all: $(LIBNAME)

$(LIBNAME): $(OBJ)
	$(CXX) -shared $(CXXFLAGS) $(LDFLAGS) $(OBJ) -lc -Wl,-soname,$(SONAME) $(LSFLAGS) -o $(LIBNAME)
	ln -s $(LIBNAME) $(SONAME)
	ln -s $(SONAME) lib$(TARGET).so

.c.o:
	$(CXX) -fPIC -c $(CXXFLAGS) -o $*.o $<

$(TARGET).o: .depend $(OBJ)

clean:
	rm -f $(OBJ) *~ core .depend $(SONAME)

cleanall: clean
	rm -f ../$(TARGET)Dep.h ../$(TARGET)Itf.h

.depend:
	$(CXX) $(CXXFLAGS) -M $(SRC) > $@

ifeq (.depend,$(wildcard .depend))
include .depend
endif

