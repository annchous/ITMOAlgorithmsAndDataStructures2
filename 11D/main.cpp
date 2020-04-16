#include <iostream>
#include <fstream>
#include <vector>

struct Edge {
    int to;
    long long weight;
};

int N;
int M;
int S;
const long long INF = 8e18;
std::vector<std::vector<Edge>> G;
std::vector<long long> dist;
std::vector<bool> negCycle;
std::vector<bool> isVisited;

void DFS1(int v) {
    isVisited[v] = true;
    for (auto &e : G[v]) {
        if (!isVisited[e.to]) {
            DFS1(e.to);
        }
    }
}

void DFS2(int v) {
    negCycle[v] = true;
    for (auto &e : G[v]) {
        if (!negCycle[e.to]) {
            DFS2(e.to);
        }
    }
}

void FordBellman() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (auto &e : G[j]) {
                if (dist[j] + e.weight < dist[e.to]) {
                    dist[e.to] = std::max(-INF, dist[j] + e.weight);
                    if (i == N - 1 && isVisited[e.to]) {
                        DFS2(e.to);
                    }
                }
            }
        }
    }
}

int main() {
    std::ifstream in("path.in");
    std::ofstream out("path.out");

    in >> N >> M >> S;
    S--;
    G.resize(N);
    dist.resize(N, INF);
    negCycle.resize(N, false);
    isVisited.resize(N, false);

    int from;
    Edge edge{};
    for (int i = 0; i < M; ++i) {
        in >> from >> edge.to >> edge.weight;
        edge.to--;
        G[from - 1].push_back(edge);
    }

    dist[S] = 0;
    DFS1(S);
    FordBellman();

    for (int u = 0; u < N; ++u) {
        if (negCycle[u] || dist[u] < -INF) {
            out << "-\n";
        }
        else if (!isVisited[u]) {
            out << "*\n";
        }
        else {
            out << dist[u] << "\n";
        }
    }

    return 0;
}