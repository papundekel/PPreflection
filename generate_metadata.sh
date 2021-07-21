#!/bin/bash
if [ "$#" -ne 2 ]; then
  echo "Bad argument count. \$1: PPreflector dynamic library, \$2: the name of the reflected .cpp file." >&2
  exit 1
fi

touch "$2".meta && clang++-12 -std=c++20 -fplugin="$1" -fsyntax-only "$2"
