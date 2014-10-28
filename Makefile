# $Id: Makefile,v 1.1 2002/12/06 14:25:18 marquet Exp $
##############################################################################

ROOTDIR=./libhardware/

CC	= gcc
CFLAGS	= -Wall -ansi -pedantic
LIBDIR  = -L$(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -lhardware

###------------------------------
### Main targets 
###------------------------------------------------------------
BINARIES= mkhd dmps frmt mkvol dvol
OBJECTS	= drive.o dmps.o frmt.o mkhd.o mkvol.o dvol.o

all: $(BINARIES) $(OBJECTS)

###------------------------------
### Binaries
###------------------------------------------------------------
mkhd: mkhd.o mbr.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIBS)

dmps: dmps.o drive.o mbr.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIBS)

dvol: dvol.o mbr.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIBS)

frmt: frmt.o drive.o mbr.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIBS)

mkvol: mkvol.o mbr.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIBS)

###------------------------------
### #include dependences 
###------------------------------------------------------------
# you may fill these lines with "make depend"
mkhd.o: mkhd.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

dmps.o: dmps.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

frmt.o: frmt.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

drive.o: drive.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

mkvol.o: mkvol.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

dvol.o: dvol.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

mbr.o: mbr.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

vol.o: vol.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean 
	$(RM) vdiskA.bin vdiskB.bin
depend : 
	$(CC) -MM $(INCDIR) *.c

