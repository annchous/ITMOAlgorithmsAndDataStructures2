#include <iostream>
#include <vector>

std::vector<int> PrefixFunction(std::string s) {
    std::vector<int> p;
    p.assign(s.length(), 0);
    for (int i = 1; i < s.length(); ++i) {
        int k = p[i - 1];
        while (k > 0 && s[i] != s[k]) {
            k = p[k - 1];
        }
        if (s[i] == s[k]) {
            k++;
        }
        p[i] = k;
    }
    return p;
}

int main() {
    int n;
    std::string s;
    std::cin >> n;
    std::cin >> s;

    s += "#";
    std::vector<int> prefix = PrefixFunction(s);
    std::vector<std::vector<int>> KMP(s.length(), std::vector<int>(n));

    for (int i = 0; i < s.length(); ++i) {
        for (char c = 'a'; c < 'a' + n; ++c) {
            if (i > 0 && c != s[i]) {
                KMP[i][c - 'a'] = KMP[prefix[i - 1]][c - 'a'];
            }
            else {
                KMP[i][c - 'a'] = i + (c == s[i]);
            }
        }
    }

    for (auto& row : KMP) {
        for (auto& i : row) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}