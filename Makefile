##Makefile for Frugal Distributed Media Network Server##

CC=g++
CFLAGS= -O3 -Iinclude -Ilib

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
LIBDIR = lib

LIB_OBJS = iniReader_linux_x86_64.o
_LIB_OBJS = $(patsubst %,$(LIBDIR)/%, $(LIB_OBJS))

LIB_OBJS_WIN = iniReader_win_x86_64.o
_LIB_OBJS_WIN = $(patsubst %,$(LIBDIR)/%, $(LIB_OBJS_WIN))

SERVER_DEPS = interface.o server_core.o settings.o logging.o
_SERVER_DEPS = $(patsubst %,$(OBJDIR)/%,$(SERVER_DEPS))

CMD_OBJS = cmd_a.o cmd_t.o
_CMD_OBJS = $(patsubst %,$(OBJDIR)/%, $(CMD_OBJS))

vpath %.cpp $(SRCDIR)
vpath %.cpp $(SRCDIR)/admin
vpath %.cpp $(SRCDIR)/admin/cmd_bindings

vpath %.h $(INCDIR)
vpath %.h $(INCDIR)/admin
vpath %.h $(INCDIR)/admin/cmd_bindings

vpath %.o $(LIBDIR)
vpath %.o $(OBJDIR)

fdmn_server: fdmn.cpp fdmn.h $(SERVER_DEPS)
	$(CC) $(SRCDIR)/fdmn.cpp $(CFLAGS) $(_SERVER_DEPS) $(_CMD_OBJS) $(_LIB_OBJS) -o $(BINDIR)/$@

fdmn_server_debug:
	make LIB_OBJS='iniReader_linux_x86_64_debug.o'

fdmn_server_win: fdmn.cpp fdmn.h $(SERVER_DEPS)
	$(CC) $(SRCDIR)/fdmn.cpp $(CFLAGS) $(_SERVER_DEPS) $(_CMD_OBJS) $(_LIB_OBJS_WIN) -o $(BINDIR)/$@

%.o: %.cpp %.h
	$(CC) -c $< -o $(OBJDIR)/$@ $(CFLAGS)

interface.o: interface.cpp interface.h $(CMD_OBJS)
	$(CC) -c $< -o $(OBJDIR)/$@ $(CFLAGS)

run_server: fdmn_server
	$(BINDIR)/fdmn_server settings.ini

run_server_win: fdmn_server_win
	bin\$^.exe settings.ini

clean:
	rm -f $(BINDIR)/fdmn_server
	rm $(OBJDIR)/*.o
