#!/bin/bash
# wrap-enum.sh: Run the equivalent of _WRAP_ENUM.  Run this in the
# include directory.
# Copyright (c) Chris White, 2016.

gawk -- '
  BEGIN { inblock=0; blockname=""; prevline="" }
  (!inblock) && ($0 ~ /^ \* G[A-Za-z]+:/) { # enum-block start
    blockname=$2
    sub(/\<G/,"", blockname)
    sub(/:/,"", blockname)
    sub(/\<G/,"", $2)
    print prevline  # which we suppressed since we were not in a block
    print
    inblock=1
    prevline=$0
    next
  }
  (!inblock) { prevline=$0; next } # do not print outside the enums
  inblock {
    sub(/\<G_/,""); 
    if($0 ~ ("^} G" blockname)) {   # enum-block end
      sub("G" blockname, blockname, $2)
      inblock=0
    }
    print
    prevline=$0
  }
'

# vi: set ts=2 sts=2 sw=2 et ai ff=unix: #

