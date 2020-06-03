#!/bin/bash

cd build

rm -rf *

cmake .. -G "CodeBlocks - Unix Makefiles"

make
