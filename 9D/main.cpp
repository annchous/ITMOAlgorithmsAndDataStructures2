#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

vector<vector<int>> G;
vector<vector<int>> H;
vector<int> order;
vector<int> component;
vector<bool> isVisited;

void DFS1(int v) {
    isVisited[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        if (!isVisited[G[v][i]]) {
            DFS1(G[v][i]);
        }
    }
    order.push_back(v);
}

void DFS2(int v, int k) {
    component[v] = k;
    for (int i = 0; i < H[v].size(); i++) {
        if (component[H[v][i]] == -1) {
            DFS2(H[v][i], k);
        }
    }
}
int main() {
    ifstream in("cond.in");
    ofstream out("cond.out");
    G.resize(100000);
    H.resize(100000);

    int n, m;
    in >> n >> m;
    isVisited.assign(n, false);
    component.assign(n, -1);
    int x, y;
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        G[x-1].push_back(y-1);
        H[y-1].push_back(x-1);
    }
    for (int i = 0; i < n; i++) {
        if (!isVisited[i]) {
            DFS1(i);
        }
    }
    int k = 1;
    reverse(order.begin(), order.end());
    for (int v : order) {
        if (component[v] == -1) {
            DFS2(v, k);
            k++;
        }
    }
    out << k - 1 << endl;
    for (int &comp: component) {
        out << comp << " ";
    }
    return 0;
}