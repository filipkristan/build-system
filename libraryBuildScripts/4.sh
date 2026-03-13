#!/bin/bash

depriv() {
  if [[ $SUDO_USER ]]; then
    sudo -u "$SUDO_USER" -- "$@"
  else
    "$@"
  fi
}

{
if [ ! -f /usr/local/include/raylib.h ]; then
    echo "Raylib not found!"
    echo "Installing Raylib..."
    rm -rf raylib-5.5.*
    depriv curl https://github.com/raysan5/raylib/archive/refs/tags/5.5.zip -L -O -J
    depriv unzip raylib-5.5.zip
    depriv cd raylib-5.5 && mkdir raylib-5.5/build && cd raylib-5.5/build && cmake ..
    cd raylib-5.5/build && make install
    rm -rf raylib-5.5.*
    exit 0
fi
}

