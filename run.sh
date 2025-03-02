#!/bin/bash

path="/home/landotech/GitHub/CalculatorApp"
cd "$path"/build

cmake build .
make
./calc
