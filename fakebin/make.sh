#!/bin/sh -x
x86_64-w64-mingw32-gcc -o runcmd runcmd.cc
strip -p runcmd.exe
for f in ls chmod; do
  cp -pf runcmd.exe $f.exe
done
