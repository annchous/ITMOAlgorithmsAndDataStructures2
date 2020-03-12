#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> G;
int n, m;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> n >> m;
    G.resize(n);
    int x, y;
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        G[x-1].push_back(y-1);
        G[y-1].push_back(x-1);
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int &v : G[i]) {
            k++;
        }
        out << k << " ";
        k = 0;
    }
    return 0;
}