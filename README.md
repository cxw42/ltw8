# ltw8
A lightweight C++11 UTF-8 string-handling library.  Coming soon!

## Organization

This library is Glib::ustring, extracted from gtkmm and hacked to compile
without glib.  **Do not use this in a GNOME/gtk application!**

Rather than making code edits, I have used preprocessor hackery whenever
possible.  My hope is that this will make it easier to merge upstream
changes.

## Branches

 - master: mainline development and releases.
 - upstream_gnome: branch that only pulls in updates to glib and glibmm.

### Upstream flow

When glib or glibmm is updated, update the upstream_gnome branch with the new
files.  Then merge upstream_gnome into master, --no-ff.  Then make code changes
in master as necessary.

### Upstream sources:

 - glib: https://github.com/GNOME/glib
 - glibmm: https://github.com/GNOME/glibmm

## Copyright

This is not an official GNOME project, nor is it related in any way to
GNOME or GTK.

New code is copyright (c) Chris White (cxw42), 2016.  See file LICENSE
for details.

