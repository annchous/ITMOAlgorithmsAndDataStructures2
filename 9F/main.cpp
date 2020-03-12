#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

vector<vector<int>> G;
vector<bool> isVisited;
vector<int> mark;

void DFS(int v) {
    isVisited[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        if (!isVisited[G[v][i]]) {
            DFS(G[v][i]);
            if (mark[G[v][i]] == 0) {
                mark[v] = 1;
            }
        }
        else if (isVisited[G[v][i]]) {
            if (mark[G[v][i]] == 0) {
                mark[v] = 1;
            }
        }
    }
}

int main() {
    ifstream in("game.in");
    ofstream out("game.out");
    G.resize(100000);

    int n, m, startV;
    in >> n >> m >> startV;
    startV--;
    isVisited.assign(n, false);
    mark.assign(n, 0);
    int x, y;
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        G[x-1].push_back(y-1);
    }
    for (int i = 0; i < n; i++) {
        if (!isVisited[i]) {
            DFS(i);
        }
    }
    if (mark[startV]) {
        out << "First player wins" << endl;
    }
    else out << "Second player wins" << endl;

    return 0;
}