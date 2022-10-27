#!/bin/sh

set -x

SOURCE_DIR=$(pwd)
BUILD_DIR=${BUILD_DIR:-../build}
BUILD_TYPE=${BUILD_TYPE:-release}
INSTALL_DIR=${INSTALL_DIR:-../${BUILD_TYPE}-install-jcb}
CXX=${CXX:-g++}



mkdir -p $BUILD_DIR/$BUILD_TYPE-proxy-jcb \
  && cd $BUILD_DIR/$BUILD_TYPE-proxy-jcb \
  && cmake \
           -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
           -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR \
           -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
           $SOURCE_DIR \
  && make -j10

# Use the following command to run all the unit tests
# at the dir $BUILD_DIR/$BUILD_TYPE :
# CTEST_OUTPUT_ON_FAILURE=TRUE make test

# cd $SOURCE_DIR && doxygen

