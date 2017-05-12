#!/bin/bash
arg=("$@")
for ((i=0; i<${#arg[*]}; i++)); do
  case "${arg[$i]}" in
    [A-Z]:[/\\]*|*\\*) arg[$i]=$(/usr/bin/cygpath "${arg[$i]}");;
  esac
done
set -x
exec /usr/bin/ls "${arg[@]}"
