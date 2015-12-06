#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int parent[200001], rk[200001];

int compress(int node) {
    return (parent[node] == -1 ? node : parent[node] = compress(parent[node]));
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
		cerr << "Missing argument. Expected format: in_file out_file\n";
	    return 0;
    }
	
	ifstream in(argv[1]);
    if (!in.is_open()) {
		cerr << "Unable to open read file.\n";
	    return 0;
    }

    ofstream out(argv[2]); 
    if (!out.is_open()) {
		cerr << "Unable to open write file.\n";
		return 0;
	}

    int n, m;
    in >> n >> m;
    
    vector < pair < double, pair < int, int > > > edges;
    for (int i = 0; i < m; ++i) {
        int x, y;
        double w;
        in >> x >> y >> w;
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

    out << ans;
    
    return 0;
}
