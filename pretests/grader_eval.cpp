#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 500005;

const double eps = 0.000001;

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

pair < bool, double > find_in_edges(int x, int y) {
    int step = 1 << 20, i;

    for (i = 0; step; step >>= 1)
        if (i + step < edges.size() && (edges[i + step].first < x || (edges[i + step].first == x && edges[i + step].second.first < y)))
            i += step;

    if (i + 1 < edges.size() && edges[i + 1].first == x && edges[i + 1].second.first == y)
        return make_pair(true, edges[i + 1].second.second);

    return make_pair(false, 0);
}

int main() {
    freopen("test.in", "r", stdin);
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

    freopen("test.ok", "r", stdin); 

    double answer;
    scanf("%lf", &answer);

    fclose(stdout);

    freopen("test.out", "r", stdin);
    
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

    double check = 0;
    for (int i = 0; i < edg; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);

        pair < bool, double > p = find_in_edges(x, y);

        if (!p.first) {
            fprintf(stderr, "WA: Illegal edge.\n");
            return 0;
        } else {
            check += p.second;
        }

        int rx = compress(x);
        int ry = compress(y);

        if (rx == ry) {
            fprintf(stderr, "WA: Not a tree.\n");
            return 0;
        }

        parent[rx] = ry;
    }

    if (!equal(check, user_answer)) {
        fprintf(stderr, "WA: The tree doesn't respect the requirements.\n");
        return 0;
    }
    
    fprintf(stderr, "OK\n");
    return 1;
}
