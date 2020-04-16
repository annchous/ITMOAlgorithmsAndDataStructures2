#include <iostream>
#include <fstream>
#include <vector>

struct Edge {
    int to;
    long long w;
};

int N;
int M;
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
    std::ifstream in("pathsg.in");
    std::ofstream out("pathsg.out");

    in >> N >> M;

    G.resize(N);
    dist.resize(N, infinity);
    isVisited.resize(N, false);

    int from;
    int to;
    long long weight;
    Edge edge{};

    for (int i = 0; i < M; ++i) {
        in >> from >> to >> weight;
        from--;
        to--;
        edge.to = to;
        edge.w = weight;
        G[from].push_back(edge);
    }

    for (int i = 0; i < N; i++) {
        dist.assign(N, infinity);
        isVisited.assign(N, false);
        dist[i] = 0;
        Dijkstra();
        for (auto &it : dist) {
            out << it << " ";
        }
        out << std::endl;
    }

    return 0;
}