#include <iostream>
#include <fstream>
#include <vector>

int N;
int M;
int K;

std::vector<std::vector<int>> G;
std::vector<bool> isVisited;
std::vector<int> matching;

bool DFS(int v) {
    if (isVisited[v]) {
        return false;
    }
    isVisited[v] = true;
    for (auto &to : G[v]) {
        if (matching[to] == -1 || DFS(matching[to])) {
            matching[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    std::ifstream in("matching.in");
    std::ofstream out("matching.out");

    in >> N >> M >> K;
    G.resize(N);
    isVisited.resize(N);
    matching.resize(M, -1);
    int from, to;
    int maxMatching = 0;
    for (int i = 0; i < K; ++i) {
        in >> from >> to;
        from--;
        to--;
        G[from].push_back(to);
    }

    for (int i = 0; i < N; ++i) {
        isVisited.assign(N, false);
        if (DFS(i)) {
            maxMatching++;
        }
    }

    out << maxMatching;


    return 0;
}