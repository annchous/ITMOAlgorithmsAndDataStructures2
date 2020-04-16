#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

int N;
int M;
std::vector<long long> dist;
std::vector<bool> isVisited;
const long long infinity = 2e18;
std::vector<std::vector<std::pair<long long, int>>> G;
std::set<std::pair<long long, int>> set;

void Dijkstra(int source) {
    set.insert(std::make_pair(dist[source], source));
    while (!set.empty()) {
        int v = set.begin()->second;
        set.erase(set.begin());
        for (int i = 0; i < G[v].size(); ++i) {
            if (dist[v] + G[v][i].first < dist[G[v][i].second]) {
                set.erase(std::make_pair(G[v][i].first, G[v][i].second));
                dist[G[v][i].second] = dist[v] + G[v][i].first;
                set.insert(std::make_pair(dist[G[v][i].second], G[v][i].second));
            }
        }
    }
}

int main() {
    std::ifstream in("pathbgep.in");
    std::ofstream out("pathbgep.out");

    in >> N >> M;

    G.resize(N);
    dist.resize(N, infinity);
    isVisited.resize(N, false);

    int from;
    int to;
    long long weight;

    for (int i = 0; i < M; ++i) {
        in >> from >> to >> weight;
        from--;
        to--;
        G[from].push_back(std::make_pair(weight, to));
        G[to].push_back(std::make_pair(weight, from));
    }

    dist[0] = 0;
    Dijkstra(0);

    for (auto &it : dist) {
        out << it << " ";
    }

    return 0;
}