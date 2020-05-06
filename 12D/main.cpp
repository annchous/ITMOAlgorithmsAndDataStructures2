#include <fstream>
#include <queue>
#include <algorithm>

struct Edge {
    int to;
    int capacity;
    int flow;
};

std::vector<std::vector<int>> G;
std::vector<std::vector<int>> ans;
std::vector<Edge> E;
std::vector<int> p;
std::vector<int> d;

int N;
int M;
int S;
int T;

bool BFS() {
    d.assign(N, 0);
    std::queue<int> Q;
    Q.push(S);
    d[S] = 1;
    while (!Q.empty() && !d[T]) {
        int v = Q.front();
        Q.pop();
        for (auto& edge : G[v]) {
            if (!d[E[edge].to] && E[edge].flow < E[edge].capacity) {
                Q.push(E[edge].to);
                d[E[edge].to] = d[v] + 1;
            }
        }
    }
    return d[T];
}

int DFS(int v, int flow) {
    if (!flow)
        return 0;
    if (v == T)
        return flow;
    while (p[v] < G[v].size()) {
        int edge = G[v][p[v]];
        if (d[v] + 1 == d[E[edge].to]) {
            int delta = DFS(E[edge].to, std::min(flow, E[edge].capacity - E[edge].flow));
            if (delta) {
                E[edge].flow += delta;
                E[edge ^ 1].flow -= delta;
                return delta;
            }
        }
        p[v]++;
    }
    return 0;
}

int main() {
    std::ifstream in("circulation.in");
    std::ofstream out("circulation.out");

    in >> N >> M;
    N += 2;
    G.resize(N);
    p.resize(N, 0);
    S = 0;
    T = N - 1;
    int position = 0;
    for (int i = 0; i < M; ++i) {
        int from, to, lowFlow, highFlow;
        in >> from >> to >> lowFlow >> highFlow;
        G[S].push_back(position);
        E.emplace_back(Edge{to, lowFlow, 0});
        position++;
        G[to].push_back(position);
        E.emplace_back(Edge{S, 0, 0});
        position++;
        G[from].push_back(position);
        E.emplace_back(Edge{to, highFlow - lowFlow, 0});
        position++;
        G[to].push_back(position);
        E.emplace_back(Edge{from, 0, 0});
        position++;
        G[from].push_back(position);
        E.emplace_back(Edge{T, lowFlow, 0});
        position++;
        G[T].push_back(position);
        E.emplace_back(Edge{from, 0, 0});
        position++;
    }

    while (BFS()) {
        while (DFS(S, INT32_MAX));
        p.assign(N, 0);
    }

    bool noCirculation = false;
    for (int& edge : G[0]) {
        if (E[edge].flow < E[edge].capacity) {
            noCirculation = true;
        }
    }

    if (!noCirculation) {
        out << "YES\n";
        for (int i = 0; i < E.size(); i += 6) {
            out << E[i + 2].flow + E[i + 4].flow << "\n";
        }
    }
    else out << "NO\n";
    return 0;
}