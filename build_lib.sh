#!/bin/bash
g++ -c lib/sum.cpp -o lib/sum.o
ar rcs lib/libsum.a lib/sum.o
