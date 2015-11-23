#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int parent[200001], rk[200001];

int compress(int node) {
    return (parent[node] == -1 ? node : parent[node] = compress(parent[node]));
}

int main() {
    freopen("test.in", "r", stdin);
    freopen("test.ok", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);
    
    vector < pair < double, pair < int, int > > > edges;
    for (int i = 0; i < m; ++i) {
        int x, y;
        double w;
        scanf("%d%d%lf", &x, &y, &w);
        edges.push_back(make_pair(w, make_pair(x, y)));
    }

    sort(edges.begin(), edges.end());

    for (int i = 0; i < n; ++i) {
        parent[i] = - 1;
        rk[i] = 1;
    }

    double ans = 0;
    vector < pair < int, int > > v;
    for (int i = 0; i < edges.size(); ++i) {
        int rx = compress(edges[i].second.first);
        int ry = compress(edges[i].second.second);
        if (rx != ry) {
            if (rk[rx] > rk[ry]) {
                parent[ry] = rx;
                rk[rx] += rk[ry];
            } else {
                parent[rx] = ry;
                rk[ry] += rk[rx];
            }
            v.push_back(edges[i].second);
            ans += edges[i].first;
        }
    } 

    printf("%lf\n", ans);
    /*printf("%d\n", (int)v.size());

    for (int i = 0; i < v.size(); ++i)
        printf("%d %d\n", v[i].first, v[i].second); */

    return 0;
}
