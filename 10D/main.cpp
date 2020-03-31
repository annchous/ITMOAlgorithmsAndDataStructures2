#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int w;
};

vector<bool> isVisited;
vector<int> order;
vector<int> component;

void DFS(vector<vector<Edge>> &G, int v) {
    isVisited[v] = true;
    for (Edge i : G[v]) {
        if (!isVisited[i.to]) {
            DFS(G, i.to);
        }
    }
}

bool Checker(int n) {
    for (int i = 0; i < n; i++) {
        if (!isVisited[i]) {
            return false;
        }
    }
    return true;
}

void DFS1(vector<vector<Edge>> &G, int v) {
    isVisited[v] = true;
    for (Edge i : G[v]) {
        if (!isVisited[i.to]) {
            DFS1(G, i.to);
        }
    }
    order.push_back(v);
}

void DFS2(vector<vector<Edge>> &H, int v) {
    isVisited[v] = true;
    component.push_back(v);
    for (Edge i : H[v]) {
        if (!isVisited[i.to]) {
            DFS2(H, i.to);
        }
    }
}

void Condensation(vector<vector<Edge>> &G, vector<int> &comp, int &k) {
    vector<vector<Edge>> H(G.size());
    Edge reversedEdge{};
    for (int i = 0; i < G.size(); i++) {
        for (Edge e : G[i]) {
            reversedEdge.to = i;
            H[e.to].push_back(reversedEdge);
        }
    }
    isVisited.assign(G.size(), false);
    order.clear();
    for (int i = 0; i < G.size(); i++) {
        if (!isVisited[i]) {
            DFS1(G, i);
        }
    }
    isVisited.assign(G.size(), false);
    for (int i = H.size() - 1; i >= 0; i--) {
        if (!isVisited[order[i]]) {
            DFS2(H, order[i]);
            for (int c : component) {
                comp[c] = k;
            }
            k++;
            component.clear();
        }
    }
}

long long FindMST(vector<vector<Edge>> &G, int n, int root) {
    long long res = 0;
    vector<int> minEdge(n);
    minEdge.assign(n, 1000000000);
    for (vector<Edge> x : G) {
        for (Edge e : x) {
            minEdge[e.to] = min(e.w, minEdge[e.to]);
        }
    }
    for (int v = 0; v < n; v++) {
        if (v != root) {
            res += minEdge[v];
        }
    }
    vector<vector<Edge>> zeroEdges(n);
    for (int i = 0; i < G.size(); i++) {
        for (Edge e : G[i]) {
            if (e.w == minEdge[e.to]) {
                zeroEdges[i].push_back(e);
            }
        }
    }
    isVisited.assign(n, false);
    DFS(zeroEdges, root);
    if (Checker(n)) return res;
    int k = 0;
    vector<int> comp(n);
    Condensation(zeroEdges, comp, k);
    vector<vector<Edge>> newEdges(k);
    Edge newEdge{};
    for (int i = 0; i < G.size(); i++) {
        for (Edge e : G[i]) {
            if (comp[i] != comp[e.to]) {
                newEdge.to = comp[e.to];
                newEdge.w = e.w - minEdge[e.to];
                newEdges[comp[i]].push_back(newEdge);
            }
        }
    }
    res += FindMST(newEdges, k, comp[root]);
    return res;
}

int main() {
    ifstream in("chinese.in");
    ofstream out("chinese.out");

    int n, m;
    in >> n >> m;
    vector<vector<Edge>> G(n);
    isVisited.resize(n, false);
    Edge edge{};
    int from, to, weight;
    for (int i = 0; i < m; i++) {
        in >> from >> to >> weight;
        from--;
        to--;
        edge.to = to;
        edge.w = weight;
        G[from].push_back(edge);
    }

    DFS(G, 0);
    if (!Checker(n)) out << "NO";
    else {
        out << "YES" << endl;
        out << FindMST(G, n, 0) << endl;
    }

    return 0;
}