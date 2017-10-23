#!/bin/bash
set -ex

SRC_DIR=$(dirname "$0")
mkdir /tmp/build
cd /tmp/build
cmake "${SRC_DIR}"
cmake --build .
ctest -V