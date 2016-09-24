# ltw8/src/Makefile
# Copyright (c) 2016 Chris White

# Note: the pkg-config command below omits glibmm-2.4 since we are extracting
# only the relevant bits of glibmm.
# The -I*sigc++* are from the pkg-config line for glibmm-2.4.

LIBS=-lgobject-2.0 -lglib-2.0 -lintl -lsigc-2.0
	# from pkg-config for glibmm-2.4

all: stringutils.o ustring.o error.o exception.o exceptionhandler.o wrap.cc

.cc.o:
	g++ -c --std=c++11 $< -I../include -I. `pkg-config --cflags --libs glib-2.0` -I/usr/include/sigc++-2.0 -I/usr/lib/sigc++-2.0/include -o $@

# vi: set ff=unix: #

