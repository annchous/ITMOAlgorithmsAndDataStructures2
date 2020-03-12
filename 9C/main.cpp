#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> G;
vector<int> color;
bool bipartite;

void DFS(int v) {
    for (int i = 0; i < G[v].size(); i++) {
        if (color[G[v][i]] == 0) {
            color[G[v][i]] = 3 - color[v];
            DFS(G[v][i]);
        }
        else if (color[G[v][i]] == color[v]) {
            bipartite = false;
            return;
        }
    }
}

int main() {
    ifstream in("bipartite.in");
    ofstream out("bipartite.out");

    int n, m;
    in >> n >> m;
    G.resize(100000);
    color.resize(100000);
    int x, y;
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        G[x-1].push_back(y-1);
        G[y-1].push_back(x-1);
    }
    bipartite = true;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            color[i] = 1;
            DFS(i);
            if (!bipartite) {
                break;
            }
        }
    }
    if (bipartite) {
        out << "YES";
    }
    else {
        out << "NO";
    }
    return 0;
}