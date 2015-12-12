#ifndef _TSP_HEADER_
#define _TSP_HEADER_

int* travelling_salesman_problem(graph* g);
double cost_travelling_salesman_problem(int* ord, graph* g);

// BOUNDS
int travelling_salesman_problem_bound(graph* g);
int cost_travelling_salesman_problem_bound(int* ord, graph* g);

#endif
