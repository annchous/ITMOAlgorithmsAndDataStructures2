#include <fstream>
#include <queue>
#include <algorithm>

struct Edge {
    int from;
    int to;
    int capacity;
    int flow;
    int edgeNum;
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

int Decomposition(int v, int flow) {
    if (v == T) {
        ans.emplace_back();
        return flow;
    }
    for (int edge : G[v]) {
        if (E[edge].flow > 0) {
            int delta = Decomposition(E[edge].to, std::min(flow, E[edge].flow));
            if (delta) {
                ans.back().push_back(E[edge].edgeNum);
                if (v == S) {
                    ans.back().push_back(ans[ans.size() - 1].size());
                    ans.back().push_back(delta);
                    reverse(ans.back().begin(), ans.back().end());
                }
                E[edge].flow -= delta;
                return delta;
            }
        }
    }
    return 0;
}

int main() {
    std::ifstream in("decomposition.in");
    std::ofstream out("decomposition.out");

    in >> N >> M;
    G.resize(N);
    p.resize(N, 0);
    S = 0;
    T = N - 1;
    int position = 0;
    for (int i = 0; i < M; ++i) {
        int from, to, capacity;
        in >> from >> to >> capacity;
        from--;
        to--;
        G[from].push_back(position);
        E.emplace_back(Edge{from, to, capacity, 0, i});
        position++;
        G[to].push_back(position);
        E.emplace_back(Edge{to, from, 0, 0, i});
        position++;
    }

    while (BFS()) {
        while (DFS(S, INT32_MAX));
        p.assign(N, 0);
    }
    while (Decomposition(S, INT32_MAX));

    out << ans.size() << "\n";
    for (auto& it : ans) {
        int k = 0;
        for (auto& i : it) {
            if (k < 2) {
                out << i << " ";
            }
            else {
                out << i + 1 << " ";
            }
            k++;
        }
        out << "\n";
    }
    return 0;
}