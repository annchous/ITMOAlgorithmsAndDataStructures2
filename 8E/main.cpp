#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
// обход в глубину не находит кратчайшего пути, а находит связность
// кратчайший путь находит обход в ширину
using namespace std;

vector<vector<int>> G;
vector<bool> isVisited;

void BFS(int v, int dist[]) {
    queue<int> queue;
    queue.push(v);
    isVisited[v] = true;
    while (!queue.empty()) {
        int s = queue.front();
        queue.pop();
        for (int i = 0; i < G[s].size(); i++) {
            int next = G[s][i];
            if (!isVisited[next]) {
                isVisited[next] = true;
                queue.push(next);
                dist[next] = dist[s] + 1;
            }
        }
    }
}

int main() {
    ifstream in("pathbge1.in");
    ofstream out("pathbge1.out");

    int n, m;
    in >> n >> m;
    int dist[n];
    G.resize(n);
    isVisited.resize(n);
    int x, y;
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        G[x-1].push_back(y-1);
        G[y-1].push_back(x-1);
    }
    for (int i = 0; i < n; i++) {
        dist[i] = -1;
    }
    dist[0] = 0;
    BFS(0, dist);

    for (int i = 0; i < n; i++) {
        out << dist[i] << " ";
    }


    return 0;
}