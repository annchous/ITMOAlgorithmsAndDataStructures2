#include <iostream>
#include <cmath>
#include <vector>

int main() {
    const int x = 5;
    const int r = 655536;
    std::string s = "abacaba";
    std::string p = "aba";
    std::vector<int> ans;
    int n = s.length();
    int m = p.length();
    int hashS = (int) (std::pow(x, m - 1) * s[0] + std::pow(x, m - 2) * s[1] + std::pow(x, m - 3) * s[2]) % r;
    int hashP = (int) (std::pow(x, m - 1) * p[0] + std::pow(x, m - 2) * p[1] + std::pow(x, m - 3) * p[2]) % r;
    for (int i = 0; i <= n - m; ++i) {
        if (hashS == hashP) {
            if (s.substr(i, m) == p) {
                ans.push_back(i + 1);
            }
        }
        hashS = (int) (hashS * x - s[i] * std::pow(x, m) + s[i + m]) % r;
    }
    for (auto& i : ans) {
        std::cout << i << " ";
    }
    return 0;
}