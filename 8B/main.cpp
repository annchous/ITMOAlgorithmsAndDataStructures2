#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;
    in >> n;
    int matrix[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            in >> matrix[i][j];
        }
    }

    bool isNotOriented = true;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((matrix[i][j] == 1) && (i==j)) {
                isNotOriented = false;
                break;
            }
            else if (matrix[i][j] != matrix[j][i]) {
                isNotOriented = false;
                break;
            }
            else {
                isNotOriented = true;
            }
        }
        if (!isNotOriented) {
            break;
        }
    }

    if (isNotOriented) {
        out << "YES";
    }
    else {
        out << "NO";
    }

    return 0;
}