/* 
    Basic verifications only.
*/
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Missing argument. Expected format in_file ok_file out_file\n";
        return 0;
    }

    ifstream in(argv[1]);
    
    int n;
    in >> n;

    ifstream ok(argv[2]);
    
    double best_answer;
    ok >> best_answer;

    ifstream out(argv[3]);

    bool b[n];
    for (int i = 0; i < n; ++i)
        b[i] = false;
    
    int v[n + 1];
    for (int i = 0; i <= n; ++i)
        out >> v[i];
    
    if (v[n] != v[0]) {
        cerr << "WA: The given path is not a cycle.\n";
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        if (b[v[i]]) {
            cerr << "WA: The given cycle is not Hamiltonian.\n";
            return 0;
        }
        b[v[i]] = true;
    }

    double user_answer;
    out >> user_answer;

    if (best_answer > user_answer) {
        cerr << "WA: Impossible.\n";
        return 0;
    }

    if (user_answer > 2 * best_answer) {
        cerr << "WA: Doesn't satisfy the 2 appx condition.\n";
        return 0;
    }

    cerr << "OK\n";
    return 1;
}
