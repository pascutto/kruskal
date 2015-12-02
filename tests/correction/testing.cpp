#include <cstdio>
#include <cstdlib>
#include <string>

int main() {
    printf("Number of tests: \n");
    int Q;
    scanf("%d", &Q);
    printf("Number of vertices: \n");
    int n;
    scanf("%d", &n);
    printf("Number of edges: \n");
    int m;
    scanf("%d", &m);
    printf("Minimal value of weights: \n");
    double min;
    scanf("%lf", &min);
    printf("Maximal value of weights (exclusive): \n");
    double max;
    scanf("%lf", &max);
    
    char graphgen[100];
    sprintf(graphgen, "./graphgen.out %d %d %lf %lf test.in", n, m, min, max); // FIXME: doesn't work all the time


    for (int i = 0; i < Q; ++i) {
        system(graphgen);
        system("./ok_generator.out test.in test.ok");
        system("./main.out test.in test.out");
        system("./grader_eval.out test.in test.ok test.out");
    }

    return 0;
}
