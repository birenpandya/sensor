# File Name: makefile
# Author: Sunny Taksande
# Date: 23 June 2011
# Purpose: make file for building uart lib

# Set appropriate paths

INSTALLDIR	= ~biren/DM644/project/console  
PROJECTPATH	= $(pwd)
SOURCEPATH	= $(PROJECTPATH)/src
INCLUDEPATH	= $(PROJECTPATH)/include
BINPATH		= $(PROJECTPATH)/bin
LIBPATH		= $(PROJECTPATH)/lib
TARGETPATH	= $(BINPATH)

TARGETS		= $(TARGETPATH)/test
LIBS            = $(LIBPATH)/libuart.a

SRCFILES 	= $(SOURCEPATH)/uart.c

DEPENDANCIES	= makefile \
		$(INSTALLDIR)/include/common.h \
		$(INCLUDEPATH)/uart.h

# Compilation Flags
CC		=/media/_home/aurion/ruiva-dm355-dvsdk2/montavista/pro/devkit/arm/v5t_le/bin/arm_v5t_le-gcc
CFLAGS		= -c -I $(INCLUDEPATH) -I $(INSTALLDIR)/include

# Compilation Section

all: $(TARGETS)

$(TARGETPATH)/test: $(DEPENDANCIES) $(SRCFILES)
	$(CC) $(CFLAGS) $(SRCFILES) $(INCLUDEFLAGS) $(LIBFLAGS) -o $@


$(LIBPATH)/libuart.a: $(DEPENDANCIES) $(SRCFILES)
	$(CC) $(CFLAGS) $(SRCFILES) $(INCLUDEFLAGS)
	ar rcs $@ *.o
	rm *.o

install: $(LIBS)
	install -m666 $(LIBPATH)/libuart.a $(INSTALLDIR)/lib
	install -m666 $(INCLUDEPATH)/uart.h $(INSTALLDIR)/include

# Cleaning Section

clean:
	rm -f $(LIBS)
