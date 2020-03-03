#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> G;
vector<bool> isVisited;
vector<vector<int>> components;

void DFS(int v, int num) {
    isVisited[v] = true;
    components[v].push_back(num);
    for (int i = 0; i < G[v].size(); i++) {
        int next = G[v][i];
        if (!isVisited[next]) {
            DFS(next, num);
        }
    }
}

int main() {
    ifstream in("components.in");
    ofstream out("components.out");

    int n, m;
    in >> n >> m;
    G.resize(n);
    isVisited.resize(n);
    components.resize(n);
    int x, y;
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        G[x-1].push_back(y-1);
        G[y-1].push_back(x-1);
    }
    int num = 0;
    for (int i = 0; i < n; i++) {
        if (!isVisited[i]) {
            DFS(i, num);
            num++;
        }
    }
    out << num << endl;
    for (int i = 0; i < n; i++) {
        for (int j : components[i]) {
            out << j + 1 << " ";
        }
    }
    return 0;
}