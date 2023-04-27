#!/bin/sh -x
for f in runcmd ls chmod; do
  x86_64-w64-mingw32-gcc -o $f $f.cc
  strip -p $f.exe
done
