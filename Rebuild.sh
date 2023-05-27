#!/bin/bash

make clean
make all 2>&1 | tee ./Output/Build.log
