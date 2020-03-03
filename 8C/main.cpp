#include <iostream>
#include <fstream>

using namespace std;
int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m;
    in >> n >> m;
    int matrix[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    /*int x, y;
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        matrix[x-1][y-1] += 1;
    }

    bool hasParallelSlats = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1 && matrix[j][i] == 1 && i != j) {
                hasParallelSlats = true;
                break;
            }
            else {
                hasParallelSlats = false;
            }
        }
        if (hasParallelSlats) {
            break;
        }
    }

    if (hasParallelSlats) {
        out << "YES" << endl;
    }
    else {
        out << "NO" << endl;
    }*/
    int x, y;
    bool hasParallelSlats = false;
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        matrix[x-1][y-1] += 1;
        if (matrix[x-1][y-1] + matrix[y-1][x-1] > 1) {
            hasParallelSlats = true;
            break;
        }
        hasParallelSlats = false;
    }

    if (hasParallelSlats) {
        out << "YES" << endl;
    }
    else {
        out << "NO" << endl;
    }

    return 0;
}