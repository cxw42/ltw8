# ltw8/src/Makefile
# Copyright (c) 2016 Chris White

all: stringutils.o ustring.o error.o exception.o exceptionhandler.o

.cc.o:
	g++ -c --std=c++11 $< -I../include `pkg-config --cflags --libs glib-2.0` -o $@
	# omitting glibmm-2.4 from the pkg-config since we are extracting
	# only the relevant bits of glibmm.

# vi: set ff=unix: #

