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
    int x, y;
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        matrix[x-1][y-1] += 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            out << matrix[i][j] << " ";
        }
        out << endl;
    }
    return 0;
}