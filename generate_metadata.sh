#!/bin/bash
touch "$2".meta && clang++-12 -std=c++20 -fplugin="$1" -fsyntax-only "$2"
