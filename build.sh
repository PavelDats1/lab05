#!/bin/bash
g++ -c lib/sum.cpp -o lib/sum.o
ar rcs lib/libsum.a lib/sum.o
g++ -Ilib -c example/calc.cpp -o example/calc.o
g++ example/calc.o -Llib -lsum -o example/calc
rm -f lib/*.o example/*.o
