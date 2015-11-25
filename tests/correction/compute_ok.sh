#!/bin/bash

g++ -o ok_generator ok_generator.cpp
for file in `ls *.in`
do
	./ok_generator "$file"
done
rm -f ok_generator
