#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>

using namespace std;

int parent[200001], rk[200001];

int compress(int node) {
    return (parent[node] == -1 ? node : parent[node] = compress(parent[node]));
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
		fprintf(stderr, "Missing argument. Expected format: in_file out_file\n");
	    return 0;
    }
	
	if (!(freopen(argv[1], "r", stdin))) {
		fprintf(stderr, "Unable to open read file.\n");
	    return 0;
    }

	if (!(freopen(argv[2], "w", stdout))) {
		fprintf(stderr, "Unable to open write file.\n");
		return 0;
	}

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
    for (int i = 0; i < (int)edges.size(); ++i) {
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
            ans += edges[i].first;
        }
    } 

    printf("%lf\n", ans);
    
    return 0;
}
