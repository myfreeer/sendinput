# sendinput
keyboard and mouse input simulator for windows 

## Release
[![Latest Release](https://img.shields.io/github/release/myfreeer/sendinput.svg)](https://github.com/myfreeer/sendinput/releases/latest)
[![Download](https://img.shields.io/github/downloads/myfreeer/sendinput/total.svg)](https://github.com/myfreeer/sendinput/releases)

## Usage
See [Wiki/Usage](https://github.com/myfreeer/sendinput/wiki/Usage)

## Building
### Prerequisites
* msys2 mingw64
* git
* mingw-w64-x86_64-gcc
* mingw-w64-x86_64-cmake
* mingw-w64-x86_64-ninja

### Build script example
```bash
# Getting source
git clone https://github.com/myfreeer/sendinput
cd sendinput

# Creating folder for build
mkdir -p build
cd build

# Running cmake
cmake -GNinja ..

# Building with ninja
ninja
```

## Credits
* <https://github.com/myfreeer/win-startup-headers>