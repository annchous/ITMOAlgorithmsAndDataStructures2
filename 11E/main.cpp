#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Edge {
    int from;
    int to;
    int weight;
};

int N;
int infinity = 1e9;

std::vector<Edge> G;
std::vector<int> ans;
std::vector<int> p;
std::vector<long long> dist;

bool NegativeCycle() {
    dist[0] = 0;
    int x;
    for (int i = 0; i < N; ++i) {
        x = -1;
        for (auto &e : G) {
            if (dist[e.from] + e.weight < dist[e.to]) {
                dist[e.to] = dist[e.from] + e.weight;
                p[e.to] = e.from;
                x = e.to;
            }
        }
    }

    if (x == -1) {
        return false;
    }
    else {
        int v = x;
        for (int i = 0; i < N; ++i) {
            v = p[v];
        }
        for (int u = v; ; u = p[u]) {
            ans.push_back(u);
            if (u == v && ans.size() > 1) {
                break;
            }
        }
        std::reverse(ans.begin(), ans.end());
        return true;
    }
}

int main() {
    std::ifstream in("negcycle.in");
    std::ofstream out("negcycle.out");

    in >> N;
    G.resize(N);
    dist.resize(N, infinity);
    p.resize(N, -1);

    int w;
    Edge edge{};
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            in >> w;
            if (w != 1e9) {
                edge.from = i;
                edge.to = j;
                edge.weight = w;
                G.push_back(edge);
            }
        }
    }
    if (NegativeCycle()) {
        out << "YES\n" << ans.size() << "\n";
        for (auto &it : ans) {
            out << it + 1 << " ";
        }
    }
    else {
        out << "NO\n";
    }
    return 0;
}