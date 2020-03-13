#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> G;
vector<bool> isVisited;
stack<int> order;

void DFS(int v) {
    isVisited[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        if(!isVisited[G[v][i]]) {
            DFS(G[v][i]);
        }
    }
    order.push(v);
}

int main() {
    ifstream in("hamiltonian.in");
    ofstream out("hamiltonian.out");

    int n, m;
    in >> n >> m;
    G.resize(100000);
    isVisited.assign(n, false);
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
    bool isHamiltonian = false;
    int prevV = 0;
    int curV = 0;
    if (!order.empty()) {
        prevV = order.top();
        order.pop();
        isHamiltonian = true;
    }
    while (!order.empty()) {
        curV = order.top();
        order.pop();
        int k = 0;
        for (int &it : G[prevV]) {
            if (it == curV) {
                k++;
            }
        }
        if (k == 0) {
            isHamiltonian = false;
            break;
        }
        prevV = curV;
    }
    if (isHamiltonian) out << "YES";
    else out << "NO";
    return 0;
}
