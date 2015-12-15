# Kruskal algorithm implementation. The Trading Salesman Problem. #

Kruskal algorithm written in C for Algorithms and Programmation course (Ecole Normale Superieure, Paris).

---
## _Compilation_ ##

In order to compile, use:

`./make.sh`

All the binaries will be placed in the temporary folder `bin`  

In order to delete all the binaries and intermediary files, use:

`./make.sh clear`

## _Testing_ ##

In order to test the Kruskal Algorithm, use:

`./test.sh kruskal <verif> <nbTests> <nbNodes> <nbEdges> <minWeight> <maxWeight>`

- `<verif>` should be 1 if you want the output to be verified, 0 otherwise.

In order to test the TSP 2-approximation Algorithm, use:

`./test.sh tsp <verif> <nbNodes>`

- `<verif>` should be 1 if you want the output to be verified, 0 otherwise.

In order to test these algorithms on other test files, use:

`./src/main.out <job> <input file> <output file>`

- `<job>` should be 0 for Kruskal algorithm and 1 for TSP. 
