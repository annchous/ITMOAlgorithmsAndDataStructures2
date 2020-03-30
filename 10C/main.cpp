#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<pair<long long, pair<long long, long long>>> G;
vector<long long> parent;
long long n, m;

bool SortPair(const pair<long long, pair<long long, long long>> &p1, const pair<long long, pair<long long, long long>> &p2) {
    return p1.first < p2.first;
}

long long DSU_find_set(long long v) {
    if (v == parent[v]) return v;
    return parent[v] = DSU_find_set(parent[v]);
}

void DSU_union_sets(long long a, long long b) {
    a = DSU_find_set(a);
    b = DSU_find_set(b);
    if (a != b) {
        parent[b] = a;
    }
}

int main() {
    ifstream in("spantree3.in");
    ofstream out("spantree3.out");

    in >> n >> m;
    G.resize(m);
    parent.resize(n + 1);
    long long minWeight = 0;
    long long x, y, z;
    for (long long i = 0; i < m; i++) {
        in >> x >> y >> z;
        G[i].second.first = x;
        G[i].second.second = y;
        G[i].first = z;
    }
    for (long long i = 0; i < n; i++) {
        parent[i] = i;
    }

    sort(G.begin(), G.end(), SortPair);
    for (long long i = 0; i < m; i++) {
        long long a = G[i].second.first;
        long long b = G[i].second.second;
        long long w = G[i].first;

        if (DSU_find_set(a) != DSU_find_set(b)) {
            minWeight += w;
            DSU_union_sets(a, b);
        }
    }

    out << minWeight;
    return 0;
}