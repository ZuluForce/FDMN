##Makefile for Frugal Distributed Media Network Server##

CC=g++
CFLAGS= -O3 -Iinclude

SERVER_DEPS = interface.o
_SERVER_DEPS = $(patsubst %,$(OBJDIR)/%,$(SERVER_DEPS))

CMD_OBJS = cmd_a.o
_CMD_OBJS = $(patsubst %,$(OBJDIR)/%, $(CMD_OBJS))

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin


vpath %.cpp $(SRCDIR)
vpath %.cpp $(SRCDIR)/admin
vpath %.cpp $(SRCDIR)/admin/cmd_bindings

vpath %.h $(INCDIR)
vpath %.h $(INCDIR)/admin
vpath %.h $(INCDIR)/admin/cmd_bindings

fdmn_server: fdmn.cpp fdmn.h $(SERVER_DEPS)
	$(CC) $(SRCDIR)/fdmn.cpp $(CFLAGS) $(_SERVER_DEPS) $(_CMD_OBJS) -o $(BINDIR)/$@

%.o: %.cpp %.h
	$(CC) -c $< -o $(OBJDIR)/$@ $(CFLAGS)

interface.o: interface.cpp interface.h $(CMD_OBJS)
	$(CC) -c $< $(_CMD_OBJS) -o $(OBJDIR)/$@ $(CFLAGS)

clean:
	rm $(OBJDIR)/*.o
