#!/bin/bash

if [[ ! $1 ]]
then
	g++ -o ok_generator ok_generator.cpp
	for file in `ls *.in`
	do
		./ok_generator "$file"
	done
	rm -f ok_generator
else if [[ "$1" = "clean" ]]
then
	rm -rf *.ok
fi
fi
