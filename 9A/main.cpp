#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> G;
vector<bool> isVisited;
vector<int> ans;
vector<int> color;
int n, m;
int cycle;


void DFS(int v) {
    color[v] = 1;
    for (int i = 0; i < G[v].size(); i++) {
        int next = G[v][i];
        if (color[next] == 0) {
            DFS(next);
        }
        else if (color[next] == 1) {
            cycle = true;
            return;
        }
    }
    color[v] = 2;
    ans.push_back(v);
}

void TopSort() {
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            DFS(i);
        }
    }
    reverse(ans.begin(), ans.end());
}


int main() {
    ifstream in("topsort.in");
    ofstream out("topsort.out");

    in >> n >> m;
    G.resize(n);
    isVisited.resize(n);
    color.resize(n);
    int x, y;
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        G[x-1].push_back(y-1);
    }
    for (int i = 0; i < n; i++) {
        color[i] = 0;
    }
    cycle = false;
    TopSort();
    if (cycle) {
        out << -1;
    }
    else {
        for (int i = 0; i < ans.size(); i++) {
            out << ans[i] + 1 << " ";
        }
    }
    return 0;
}