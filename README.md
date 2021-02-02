# cppbuild

Header only C++ build system using the C/C++ language.

## Running the Demo

This simple demo will have you build the build program and execute it in order
to build the the main application which does some simple calculations and prints
them to stdout.

Currently requires g++ with C++20 support.

```bash
cd example

# Only have to do this the first time
g++ -std=c++20 build.cpp -o build.exe

./build.exe
```

Note that the if you change any of the build.cpp files, their associated
build.exe will recompile itself and build from there.

(Currently only works for the example/build.cpp file and not build.cpp files
deeper in the hierarchy because there isn't a check if the build.exe file
already exists.)
