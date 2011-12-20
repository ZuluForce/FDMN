##Makefile for Frugal Distributed Media Network Server##

CC=g++
CFLAGS= -O3 -Iinclude
LFLAGS=

SERVER_DEPS = interface.o

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

fdmn_server: fdmn.cpp fdmn.h $(SERVER_DEPS)
	$(CC) fdmn.cpp $(CFLAGS) $(LFLAGS) -o $@

%.o: %.cpp %.h
	$(CC) -c $< -o $(OBJDIR)/$@ $(CFLAGS)
	
clean:
	rm $(OBJDIR)/*.o