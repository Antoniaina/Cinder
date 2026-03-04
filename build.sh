#!/usr/bin/env bash
set -e

cd "$(dirname "$0")"

[ -d build ] || mkdir build

cd build
cmake ..
make
./minimal