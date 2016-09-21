# ltw8/src/Makefile
# Copyright (c) 2016 Chris White

all: error.o exception.o exceptionhandler.o stringutils.o ustring.o

.cc.o:
	g++ -c --std=c++11 $< `pkg-config --cflags --libs glib-2.0` -o $@
	# omitting glibmm-2.4 from the pkg-config since we are extracting
	# only the relevant bits of glibmm.

# vi: set ff=unix: #

