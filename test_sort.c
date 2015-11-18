#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n = 100000;
    
    srand(time(NULL));
    
    edge v[n];

    int i;
    for (i = 0; i < n; ++i) {
        v[i].x = rand() % 100;
        v[i].y = rand() % 100;
        v[i].w = ((double) rand()) / 666013. * 123456.;
    }

    sort(v, n);
     
    for (i = 0; i < n; ++i)
        printf("%d %d %lf\n", v[i].x, v[i].y, v[i].w);

    return 0;
}
