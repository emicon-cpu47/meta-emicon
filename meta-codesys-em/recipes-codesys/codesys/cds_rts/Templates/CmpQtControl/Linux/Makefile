######################################################################################
######################################################################################
## Copyright:»··© 3S - Smart Software Solutions GmbH, Kempten                       ##
## Program: »···Linux dynamic linking makefile                                      ##
## Module: »····Makefile                                                            ##
## Version:»····0.1                                                                 ##
## Author:      3s-software. (PhB)                                                  ##
######################################################################################

TARGET = CmpQtControl

INCLUDE = -I../ -I../../../Components -I../../../Platforms/Linux

CXX = gcc
CPP = g++

# TRG_X86 | TRG_PPC | TRG_ARM | TRG_CORTEX
CXXFLAGS = -DTRG_X86

DEBFLAGS = -g
LDLIBS = -lpthread
CXXFLAGS += -DCDECL= -DHANDLE_WIN32_PRAGMA -DDLL_DECL= -D_REENTRANT= -DHUGEPTR= 
CXXFLAGS += -O0 -Wall -Wno-unused
CXXFLAGS += $(INCLUDE)
CXXFLAGS += -DLINUX
CXXFLAGS += $(DEBFLAGS)
CXXFLAGS += -fPIC
LDFLAGS += $(LDLIBS)

CPPFLAGS = -g -O0 -D_REENTRANT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.

MAJORVER = 0
MINORVER = 1
SONAME = lib$(TARGET).so

SRC =  ../$(TARGET).c ../main.cpp
OBJ = $(SRC:.c=.o)
OBJ += $(SRC:.cpp=.o)

OBJS = ../$(TARGET).o ../main.o

all: $(SONAME)

$(SONAME): $(OBJ)
	$(CXX) -shared $(CXXFLAGS) $(LDFLAGS) $(OBJS) -lc -Wl,-soname,$(SONAME) -o $(SONAME)
	
.c.o:
	$(CXX) -fPIC -c $(CXXFLAGS) -o $*.o $<

.cpp.o:
	$(CPP) -fPIC -c $(CPPFLAGS) -o $*.o $<

$(TARGET).o: .depend $(OBJ)

clean:
	rm -f $(OBJS) *~ core .depend $(SONAME)

.depend:
	$(CXX) $(CXXFLAGS) -M $(SRC) > $@

ifeq (.depend,$(wildcard .depend))
include .depend
endif

