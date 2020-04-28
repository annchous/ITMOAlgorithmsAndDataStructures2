#include <iostream>
#include <fstream>
#include <vector>

int N;
int M;
int capacity[100][100];
std::vector<std::vector<int>> G;
std::vector<bool> isVisited;

int DFS(int v, int f) {
    if (v == N - 1) {
        return f;
    }
    isVisited[v] = true;
    for (int i = 0; i < N; ++i) {
        if (!isVisited[i] && capacity[v][i] > 0) {
            int delta = DFS(i, std::min(f, capacity[v][i]));
            if (delta > 0) {
                capacity[v][i] -= delta;
                capacity[i][v] += delta;
                return delta;
            }
        }
    }
    return 0;
}

int main() {
    std::ifstream in("maxflow.in");
    std::ofstream out("maxflow.out");

    in >> N >> M;
    G.resize(N);
    isVisited.resize(N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            capacity[i][j] = 0;
        }
    }

    int from;
    int to;
    int flowCapacity;
    for (int i = 0; i < M; ++i) {
        in >> from >> to >> flowCapacity;
        from--;
        to--;
        capacity[from][to] = flowCapacity;
        G[from].push_back(to);
    }

    int maxFlow = 0;
    int addedFlow = 0;
    do {
        isVisited.assign(N, false);
        addedFlow = DFS(0, INT32_MAX);
        maxFlow += addedFlow;
    } while (addedFlow > 0);
    out << maxFlow << std::endl;
    return 0;
}