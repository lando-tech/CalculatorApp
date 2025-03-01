#!/bin/bash

path="/home/landotech/Documents/CppProjects/CalculatorApp"
cd "$path"/build

cmake build .
make
./calc