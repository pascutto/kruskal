#include "sort.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define kMaxN 10000000

edge v[kMaxN];

int main() {
    int n = kMaxN;
    
    srand(time(NULL));
    
    int i;
    for (i = 0; i < n; ++i) {
        v[i].x = rand() % 100;
        v[i].y = rand() % 100;
        v[i].w = ((double) rand()) / 666013. * 123456.;
    }
    
    sort(v, n);
     
    int ok = 1;
    for (i = 1; i < n; ++i)
        if (v[i].w < v[i - 1].w)
            ok = 0; 

    if (ok)
        printf("OK\n");
    else
        printf("NOT OK\n");
    
    return 0;
}
