/*
DISCLAIMER:
    This source is written for the tests generated automatically with our TSP testcase generator. It is not guaranteed to works on handmade / other tests.
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

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

    double weight[n][n];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            weight[i][j] = 0;

    for (int i = 0; i < m; ++i) {
        int x, y;
        double w;
        in >> x >> y >> w;
        weight[x][y] = weight[y][x] = w;
    }

    vector < int > v;
    for (int i = 0; i < n; ++i)
        v.push_back(i);

    double ans = numeric_limits<double>::max();
    while (next_permutation(v.begin(), v.end())) {
        double ansc = 0;
        for (int i = 0; i < n - 1; ++i)
            ansc += weight[v[i]][v[i + 1]];
        ansc += weight[v[n - 1]][v[0]];

        if (ansc < ans)
            ans = ansc;
    }

    out << fixed << setprecision(7) << ans;

    return 0;
}
