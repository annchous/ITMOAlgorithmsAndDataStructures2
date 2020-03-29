#include <iostream>
#include <fstream>
#include <vector>
#include <cfloat>
#include <cmath>
#include <iomanip>

using namespace std;

vector<pair<int, int>> G;
vector<double> dist;
vector<bool> isVisited;
vector<int> path;
int n;

double CountWeight(int startV, int endV) {
    return sqrt((G[endV].first - G[startV].first) * (G[endV].first - G[startV].first) + (G[endV].second - G[startV].second) * (G[endV].second - G[startV].second));
}

int main() {
    ifstream in("spantree.in");
    ofstream out("spantree.out");

    in >> n;
    G.resize(n);
    dist.assign(n, DBL_MAX);
    isVisited.assign(n, false);
    path.resize(n, -1);
    double minWeight = 0;
    int x, y;
    for (int i = 0; i < n; i++) {
        in >> x >> y;
        G[i].first = x;
        G[i].second = y;
    }
    dist[0] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!isVisited[j] && (v == -1 || dist[j] < dist[v])) {
                v = j;
            }
        }
        isVisited[v] = true;
        if (path[v] != -1) {
            minWeight += CountWeight(v, path[v]);
        }
        for (int next = 0; next < n; next++) {
            if (CountWeight(v, next) < dist[next]) {
                dist[next] = CountWeight(v, next);
                path[next] = v;
            }
        }
    }
    out << setprecision(10) << minWeight;
    return 0;
}