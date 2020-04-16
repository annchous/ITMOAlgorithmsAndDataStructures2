#include <iostream>
#include <fstream>
#include <vector>

struct Edge {
    int to;
    long long w;
};

int N;
int S;
int F;
std::vector<long long> dist;
std::vector<bool> isVisited;
const long long infinity = 2e18;
std::vector<std::vector<Edge>> G;

void Dijkstra() {
    for (int i = 0; i < N; ++i) {
        int v = -1;
        for (int j = 0; j < N; ++j) {
            if (!isVisited[j] && (v == -1 || dist[j] < dist[v])) {
                v = j;
            }
        }

        if (dist[v] == infinity) break;
        isVisited[v] = true;

        for (int j = 0; j < G[v].size(); ++j) {
            if (dist[v] + G[v][j].w < dist[G[v][j].to]) {
                dist[G[v][j].to] = dist[v] + G[v][j].w;
            }
        }
    }
}

int main() {
    std::ifstream in("pathmgep.in");
    std::ofstream out("pathmgep.out");

    in >> N >> S >> F;

    G.resize(N);
    dist.resize(N, infinity);
    isVisited.resize(N, false);

    int x;
    Edge edge{};

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            in >> x;
            if (x != -1 && i != j) {
                edge.to = j;
                edge.w = x;
                G[i].push_back(edge);
            }
        }
    }

    dist[S - 1] = 0;

    Dijkstra();

    if (dist[F - 1] != infinity) out << dist[F - 1];
    else out << -1;

    return 0;
}