# ltw8/src/Makefile
# Copyright (c) 2016 Chris White

# Note: the pkg-config command below omits glibmm-2.4 since we are extracting
# only the relevant bits of glibmm.

all: stringutils.o ustring.o error.o exception.o exceptionhandler.o wrap.cc

.cc.o:
	g++ -c --std=c++11 $< -I../include `pkg-config --cflags --libs glib-2.0` -o $@

# vi: set ff=unix: #

