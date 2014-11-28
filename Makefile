# MAKEFILE
#
# Libraries and tests
# Author:	Leonardo Linguaglossa
# Mail:		theleos88@gmail.com
# Written:	18-November-2014
#
# - If you don't want to see those warnings, just remove the
# "pedantic" flag (or even the -Wall to delet them all).
#
# - When adding a new header file with implementation code,
# REMEMBER to add it in the DEPS and in the OBJ declaration.

#dir
IDIR =./hdr
ODIR=./obj
LDIR =./src

#lib
#i.e. math (-lm) o pthread (-lpthread)
LIBS=-lm

#param
CC=gcc
DEBUG = -g
CFLAGS= -Wall -I$(IDIR) $(DEBUG)

_DEPS = packet.h algorithm.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o packet.o algorithm.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_OBJSER = server_test.o packet.o algorithm.o
OBJSER = $(patsubst %,$(ODIR)/%,$(_OBJ))

#replaced
#%.o: %.c $(DEPS)
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)
# Another rule!
$(ODIR)/%.o: $(LDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)



# same meaning of: gcc -o test character_trie.o bloom.o crc32.o -I.
application: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

server: $(OBJSER)
	gcc server_test.c -o server obj/algorithm.o obj/packet.o 
	#gcc server_test.c -o server $(ODIR)/*  $(CFLAGS) $(LIBS)

run:
	./application

#.phony aims to avoid conflicts with same-name-file (es. a file named "clean")
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~ 

