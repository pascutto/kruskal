#!/bin/bash

cd bin

if [ "$1" == "kruskal" ]
then
	echo "Testing Kruskal algorithm."
	if [ $# -ne 7 ]
	then
		echo "Expected test.sh kruskal <check> <nbTests> <nbNodes>
		<nbEdges> <minWeight> <maxWeight>"
	else
		for i in $(seq 1 1 $3)
		do
			echo "Test case $i."
			./graphgen.out 0 $4 $5 $6 $7 test.in
			./main.out 0 test.in test.out
			if [ $2 -eq 1 ]
			then
				./ok_generator_kruskal.out test.in test.ok
				./grader_eval_kruskal.out test.in test.ok test.out
			fi
		done
	fi
elif [ "$1" == "tsp" ]
then
	echo "Testing TSP algorithm."
	if [ $# -ne 4 ]
	then
		echo "Expected test.sh tsp <check> <nbTests> <nbNodes>"
	else
		for i in $(seq 1 1 $3)
		do
			echo "Test case $i."
			./graphgen.out 1 $4 test.in
			./main.out 1 test.in test.out
			if [ $2 -eq 1 ]
			then
				if [ $4 -gt 11 ]
				then
					echo "<nbNodes> should not exceed 11."	
				else
					./ok_generator_tsp.out test.in test.ok
					./grader_eval_tsp.out test.in test.ok test.out
				fi
			fi
		done
	fi
fi

# rm -f test.*
