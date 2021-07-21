#!/bin/bash
cmake --build build/Release --config Release --target PPreflection -j 10 --
cmake --build build/Release --config Release --target PPreflector -j 10 --
