#!/bin/bash

for file in `ls *.in`
do
	./ok_generator "$file"
done
