touch "$1".meta && clang++-12 -fplugin="/home/fackop/PPreflection/build/Release/PPreflector/PPreflector.so" -fsyntax-only "$1"
