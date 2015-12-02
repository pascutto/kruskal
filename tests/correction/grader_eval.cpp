#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 500005;

const double eps = 0.00001;

vector < pair < int, pair < int, double > > > edges;

int parent[kMaxN];

int compress(int node) {
    return (parent[node] == -1 ? node : (parent[node] = compress(parent[node])));
}

double abs(double x) {
    return (x < 0 ? (-x) : x);
}

bool equal(double x, double y) {
    return (abs(x - y) < eps);
}

bool find_in_edges(int x, int y, double w) {
    int step = 1 << 20, i;

    for (i = -1; step; step >>= 1)
        if (i + step < (int)edges.size() && (edges[i + step].first < x || (edges[i + step].first == x && edges[i + step].second.first < y) || 
                                            (edges[i + step].first == x && edges[i + step].second.first == y && edges[i + step].second.second < w)))
            i += step;

    if (i + 1 < (int)edges.size() && edges[i + 1].first == x && edges[i + 1].second.first == y && equal(edges[i + 1].second.second, w))
        return true;

    return false;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Missing argument. Expected format: in_file ok_file out_file\n");
        return 0;
    }

    freopen(argv[1], "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; ++i) {
        int x, y;
        double w;
        scanf("%d%d%lf", &x, &y, &w);
        edges.push_back(make_pair(x, make_pair(y, w)));
    }
    
    sort(edges.begin(), edges.end());

    fclose(stdin);

    freopen(argv[2], "r", stdin); 

    double answer;
    scanf("%lf", &answer);

    fclose(stdout);

    freopen(argv[3], "r", stdin);
    
    double user_answer;
    scanf("%lf", &user_answer);

    if (!equal(user_answer, answer)) {
        fprintf(stderr, "WA: Not a Minimum Spanning Tree.\n");
        return 0;
    }

    int edg;
    scanf("%d", &edg);

    if (edg > n - 1) {
        fprintf(stderr, "WA: Not a Tree.\n");
        return 0;
    } else if (edg < n - 1) {
        fprintf(stderr, "WA: Not connex.\n");
        return 0;
    }

    for (int i = 0; i < n; ++i)
        parent[i] = -1;

    for (int i = 0; i < edg; ++i) {
        int x, y;
        double w;
        scanf("%d%d%lf", &x, &y, &w);

        if (!(find_in_edges(x, y, w) || find_in_edges(y, x, w))) {
            fprintf(stderr, "WA: Illegal edge %d->%d %lf.\n", x, y, w);
            return 0;
        }

        int rx = compress(x);
        int ry = compress(y);

        if (rx == ry) {
            fprintf(stderr, "WA: Not a tree.\n");
            return 0;
        }

        parent[rx] = ry;
    }

    fprintf(stderr, "OK\n");
    return 1;
}
