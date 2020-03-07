#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

vector<vector<int>> G;
vector<char> way;
typedef struct cell {
    int i;
    int j;
} cell;
int iNeighbor[4] = {-1, 0, 1, 0};
int jNeighbor[4] = {0, -1, 0, 1};
void FindTheShortestWayOut(int iStart, int jStart, int iEnd, int jEnd, int *dist[], bool *isVisited[], int n, int m) {
    int head = 0;
    int tail = 0;
    cell queue[n*m];
    isVisited[iStart][jStart] = true;
    dist[iStart][jStart] = 0;
    queue[tail].i = iStart;
    queue[tail++].j = jStart;
    while (head < tail) {
        cell v = queue[head++];
        for (int k = 0; k < 4; k++) {
            cell next;
            next.i = v.i + iNeighbor[k];
            next.j = v.j + jNeighbor[k];
            if (next.i >= 0 && next.i < n && next.j >= 0 && next.j < m) {
                if (G[next.i][next.j] != 0 && !isVisited[next.i][next.j]) {
                    isVisited[next.i][next.j] = true;
                    dist[next.i][next.j] = dist[v.i][v.j] + 1;
                    queue[tail++] = next;
                }
            }
        }
    }
}

void RecreateTheWay(int *dist[], int iEnd, int jEnd, int i, int j, int k, int n, int m, int iStart, int jStart) {
    if (dist[i][j] != 0) {
        if (i > 0 && i < n && j >= 0 && j < m && dist[i - 1][j] == dist[iEnd][jEnd] - k) {
            way.push_back('D');
            RecreateTheWay(dist, iEnd, jEnd, i - 1, j, k + 1, n, m, iStart, jStart);
        }
        else if (i >= 0 && i < n - 1 && j >= 0 && j < m && dist[i + 1][j] == dist[iEnd][jEnd] - k) {
            way.push_back('U');
            RecreateTheWay(dist, iEnd, jEnd, i + 1, j, k + 1, n, m, iStart, jStart);
        }
        else if (i >= 0 && i < n && j > 0 && j < m && dist[i][j - 1] == dist[iEnd][jEnd] - k) {
            way.push_back('R');
            RecreateTheWay(dist, iEnd, jEnd, i, j - 1, k + 1, n, m, iStart, jStart);
        }
        else if (i >= 0 && i < n && j >= 0 && j < m - 1 && dist[i][j + 1] == dist[iEnd][jEnd] - k) {
            way.push_back('L');
            RecreateTheWay(dist, iEnd, jEnd, i, j + 1, k + 1, n, m, iStart, jStart);
        }
    }
    else return;

}

int main() {

    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m;
    in >> n >> m;
    G.resize(n);
    int **dist = new int*[n];
    for (int i = 0; i < n; i++) {
        dist[i] = new int[m];
    }
    bool **isVisited = new bool*[n];
    for (int i = 0; i < n; i++) {
        isVisited[i] = new bool[m];
    }
    char square;
    int iStart = -1;
    int jStart = -1;
    int iEnd = -1;
    int jEnd = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            in >> square;
            switch (square) {
                case '.':
                    G[i].push_back(1);
                    break;
                case '#':
                    G[i].push_back(0);
                    break;
                case 'S':
                    G[i].push_back(1);
                    iStart = i;
                    jStart = j;
                    break;
                case 'T':
                    G[i].push_back(1);
                    iEnd = i;
                    jEnd = j;
                    break;
                default:
                    break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dist[i][j] = -1;
            isVisited[i][j] = false;
        }
    }

    FindTheShortestWayOut(iStart, jStart, iEnd, jEnd, dist, isVisited, n, m);
    if (dist[iEnd][jEnd] == -1) {
        out << -1;
    }
    else {
        out << dist[iEnd][jEnd] << endl;
        RecreateTheWay(dist, iEnd, jEnd, iEnd, jEnd, 1, n, m, iStart, jStart);

        for (int i = way.size() - 1; i >= 0; i--) {
            out << way[i];
        }
    }

    return 0;
}
