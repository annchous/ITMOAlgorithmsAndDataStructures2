#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> G;
vector<int> ans;
vector<int> color;
vector<int> cycleVertex;
int n, m;
bool cycle;
int startOfCycleVertex, endOfCycleVertex;

bool DFS(int v) {
    color[v] = 1;
    ans.push_back(v);
    for (int i = 0; i < G[v].size(); i++) {
        int next = G[v][i];
        if (color[next] == 0) {
            if (DFS(next)) {
                return true;
            }
        }
        else if (color[next] == 1) {
            startOfCycleVertex = next;
            endOfCycleVertex = v;
            cycle = true;
            return true;
        }
    }
    color[v] = 2;
    ans.pop_back();
    return false;
}

int main() {
    ifstream in("cycle.in");
    ofstream out("cycle.out");

    in >> n >> m;
    G.resize(100000);
    color.resize(100000);
    int x, y;
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        G[x-1].push_back(y-1);
    }
    for (int i = 0; i < G.size(); i++) {
        color[i] = 0;
    }
    cycle = false;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            if (DFS(i)) {
                break;
            }
        }
    }
    if (cycle) {
        out << "YES" << endl;
        int x, y;
        for (int i = 0; i < ans.size(); i++) {
            if (ans[i] == startOfCycleVertex) {
                x = i;
                break;
            }
        }
        for (int i = 0; i < ans.size(); i++) {
            if (ans[i] == endOfCycleVertex) {
                y = i;
                break;
            }
        }
        for (int i = x; i <= y; i++) {
            cycleVertex.push_back(ans[i]);
        }
        for (int i = 0; i < cycleVertex.size(); i++) {
            out << cycleVertex[i] + 1 << " ";
        }
    }
    else {
        out << "NO";
    }
    return 0;
}