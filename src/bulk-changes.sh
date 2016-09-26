#!/bin/bash
# bulk-changes.sh: Large-scale changes when pulling in glibmm files.
# Copyright (c) Chris White 2016.  LGPL3.

shopt -s extglob

if [[ "$#" -ge 1 ]] ; then
  items=("$@")  # save args as a list, one elem per arg.  Thanks to
                # http://stackoverflow.com/a/12711837/2877364
                # by http://stackoverflow.com/users/418413/kojiro
else
  items=(!(*.bak)) # let bash expand the glob.
fi

sed -i.bak 's/_GLIBMM_\([A-Z_]+_H\)/LTW8_\1_/g' "${items[@]}"
  # header guards
sed -i.bak 's/Glib/ltw8/g' "${items[@]}"
  # namespace changes
sed -i.bak 's/\(#include <\)glibmm\//\1/g' "${items[@]}"
  # include-path changes
sed -i.bak 's#^\(.*glibmmconfig.*\)$#//\1#' "${items[@]}"
  # don't have a glibmmconfig

# Local headers
sed -i.bak 's/#include <ustring.h>/#include "ltw8_ustring.h"/' "${items[@]}"
sed -i.bak 's/#include <unicode.h>/#include "ltw8_unicode.h"/' "${items[@]}"
sed -i.bak 's/#include <stringutils.h>/#include "ltw8_stringutils.h"/' "${items[@]}"

