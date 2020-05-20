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
    std::ifstream in("search2.in");
    std::ofstream out("search2.out");

    std::string p;
    std::string t;
    in >> p;
    in >> t;
    int n = t.length();
    int m = p.length();
    std::vector<int> ans;
    std::vector<int> prefix = PrefixFunction(p + "#" + t);
    std::cout << prefix.size() << std::endl;
    for (auto& i : prefix) {
        std::cout << i;
    }
    for (int i = 0; i < n; ++i) {
        if (prefix[m + i + 1] == m) {
            ans.push_back(i - m + 2);
        }
    }

    out << ans.size() << std::endl;
    for (auto& i : ans) {
        out << i << " ";
    }
    return 0;
}