#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#define kMaxN 1000000

using namespace std;

struct edge {
    int x, y;
    double w;
};

edge v[kMaxN];

struct edge_less {
    bool operator() (edge const& a, edge const& b) {
        return a.w < b.w;
    }
};

int main() {
    int n = kMaxN;
    clock_t begin, end;

    srand(time(NULL));

    for (int i = 0; i < n; ++i) {
        v[i].x = rand() % 100;
        v[i].y = rand() % 100;
        v[i].w = ((double) rand()) / 666013. * 123456.;
    }

    begin = clock();
    sort(v, v + n + 1, edge_less());
    end = clock();

    cout << "Time: " << (double) (end - begin) / CLOCKS_PER_SEC << "\n";

    return 0;
}

