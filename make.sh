#!/bin/bash

if [[ $# -eq 0 ]] 
then

	mkdir bin

	cd src
	make
	cp *.out ../bin/
	make clean
	cd ..

	cd tests/graphgen
	make
	cp *.out ../../bin/
	make clean
	cd ../..

	cd tests/correction
	make kruskal
	make tsp
	cp *.out ../../bin/
	make clean
	cd ../..

else 
	rm -rf bin

fi
