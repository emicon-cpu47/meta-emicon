######################################################################################
## Copyright:
## Program:
## Module:
## Version:
## Author:
#######################################################################################

CDSDIR=/svn/CodesysSpV3/trunk/CodesysSpV3/

TESTFRAMEWORKDIR=$(CDSDIR)/Test/Moduletests/Testframework/
CFLAGS += -I$(TESTFRAMEWORKDIR) -I$(TESTFRAMEWORKDIR)/../Projects/Linux/Testframework/

SIL2LINUXDIR=$(CDSDIR)/Templates/Sil2LinuxUnsafe/
PRJDIR = $(SIL2LINUXDIR)/Project/
CMPDIR = $(PRJDIR)/cmp
NETWORKLICENSEFILEDIR = /\3s\-mnt/Licenses
LIB = cc.a
LINK = $(CC) $(CFLAGS) $(LDDFLAGS) -o $@
DEBFLAGS = -g -rdynamic -DDEBUGPRINT -DRTS_DEBUG

CFLAGS += -DTRG_X86
CFLAGS += -I./ -I$(NETWORKLICENSEFILEDIR) -I$(SIL2LINUXDIR) -I$(CMPDIR) -I$(CDSDIR)/Components/ 
CFLAGS += -O0 -Wall -Wno-unused -fno-strict-aliasing -Wstrict-prototypes -fshort-wchar -m32
CFLAGS += -DLINUX  -D_GNU_SOURCE
CFLAGS += $(DEBFLAGS)
CFLAGS += -DCAALib -DNO_FENV
CFLAGS += --coverage
#CFLAGS += -DRTS_MODULETEST
LDDFLAGS +=  -T $(PRJDIR)/linkerscript.txt -lm -lrt -m32 -lgcov

TARGET = codesyscontrol

SRC = $(abspath $(wildcard $(CMPDIR)/*.c)) $(abspath $(wildcard $(SIL2LINUXDIR)/Sys/*.c))
OBJ = $(SRC:.c=.o)
OBJ += $(SIL2LINUXDIR)/Sys/SysCpuX86.o

# Safe Runtime
$(TARGET): $(LIB) MainLinux.o
	$(CC) MainLinux.o $(LIB) $(LDDFLAGS) -o $(TARGET)

$(LIB): $(OBJ)
	ar qsv $(LIB) $(OBJ)

../Sys/SysCpuX86.o: $(SIL2LINUXDIR)/Sys/SysCpuX86.s
	$(CC) $(CFLAGS) -D__ASSEMBLY__ -c $< -o $@

MainLinux.o: $(SIL2LINUXDIR)/MainLinux.c
	$(CC) $(CFLAGS) -c -o MainLinux.o $(SIL2LINUXDIR)/MainLinux.c

# workspace
workspace:
	$(shell \
	if [ ! -d $(CMPDIR) ]; \
	then mkdir $(CMPDIR);./makeworkspace.sh; fi;)

clean::
	rm -f *.o $(CMPDIR)/*.o $(SIL2LINUXDIR)/Sys/*.o $(LIB) $(TARGET) 

cleanworkspace: clean
	rm -rf $(CMPDIR) rm -rf $(SIL2LINUXDIR)/Sys/*.o












