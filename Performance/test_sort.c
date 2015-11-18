#include "sort.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define kMaxN 1000000

edge v[kMaxN];

double test(minLength) {
    clock_t begin, end;
    
    int n = kMaxN;
    
    srand(time(NULL));
    
    int i;
    for (i = 0; i < n; ++i) {
        v[i].x = rand() % 100;
        v[i].y = rand() % 100;
        v[i].w = ((double) rand()) / 666013. * 123456.;
    }
    
    begin = clock();
    sort(v, n, minLength);
    end = clock();
     
    /*int ok = 1;
    for (i = 1; i < n; ++i)
        if (v[i].w < v[i - 1].w)
            ok = 0; */

    return (double) (end - begin) / CLOCKS_PER_SEC;
}

int main() {
    int minLength = 0;

    freopen("sort_perf.csv", "w", stdout);

    for (minLength = 0; minLength <= 200; minLength += 10) {
        double tot = 0;
        int t = 0;
        
        for (t = 0; t < 100; ++t)
            tot += test(minLength);
        
        printf("%d,%lf\n", minLength, tot / 100.);
    }
    
    return 0;
}
