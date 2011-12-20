##Makefile for Frugal Distributed Media Network Server##

CC=g++
CFLAGS= -O3 -Iinclude

SERVER_DEPS = interface.o
_SERVER_DEPS = $(patsubst %,$(OBJDIR)/%,$(SERVER_DEPS))
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin


vpath %.cpp $(SRCDIR)
vpath %.cpp $(SRCDIR)/admin

vpath %.h $(INCDIR)
vpath %.h $(INCDIR)/admin

fdmn_server: fdmn.cpp fdmn.h $(SERVER_DEPS)
	$(CC) $(SRCDIR)/fdmn.cpp $(CFLAGS) $(_SERVER_DEPS) -o $(BINDIR)/$@

%.o: %.cpp %.h
	$(CC) -c $< -o $(OBJDIR)/$@ $(CFLAGS)

clean:
	rm $(OBJDIR)/*.o
