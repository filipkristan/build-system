# ABS

ABS automatically finds and installs the needed libraries.  
It also builds the C++ projects using generated build flags.

# Installation:
Run the following commands to build and install the program: 
```bash
sudo cmake -Bcmake-build-debug -H.
sudo cmake --build cmake-build-debug --target install
```

# Usage:
```bash
abs <PATH>
```
Example:
```bash
abs raylib-demo.cpp
```