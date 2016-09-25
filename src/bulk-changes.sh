#!/bin/bash
# bulk-changes.sh: Large-scale changes when pulling in glibmm files.
# Copyright (c) Chris White 2016.  LGPL3.

shopt -s extglob 

sed -i.bak 's/_GLIBMM_\([A-Z_]+_H\)/LTW8_\1_/g' *.{h,hg,cc,ccg}
  # header guards
sed -i.bak 's/Glib/ltw8/g' *.{h,hg,cc,ccg}
  # namespace changes
sed -i.bak 's/\(#include <\)glibmm\//\1/g' *.{h,hg,cc,ccg}
  # include-path changes
sed -i.bak 's#^\(.*glibmmconfig.*\)$#//\1#' *.{h,hg,cc,ccg}
  # don't have a glibmmconfig

# Local headers
sed -i.bak 's/#include <ustring.h>/#include "ltw8_ustring.h"/' !(*.bak)
sed -i.bak 's/#include <unicode.h>/#include "ltw8_unicode.h"/' !(*.bak)
sed -i.bak 's/#include <stringutils.h>/#include "ltw8_stringutils.h"/' !(*.bak)

