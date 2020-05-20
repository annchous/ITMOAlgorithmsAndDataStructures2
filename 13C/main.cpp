#include <fstream>
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
    std::ifstream in("prefix.in");
    std::ofstream out("prefix.out");

    std::string s;
    in >> s;
    std::vector<int> prefix = PrefixFunction(s);
    for (auto& i : prefix) {
        out << i << " ";
    }
    return 0;
}