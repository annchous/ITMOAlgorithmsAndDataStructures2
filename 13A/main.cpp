#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::ifstream in("search1.in");
    std::ofstream out ("search1.out");

    std::string p;
    std::string t;
    std::vector<int> ans;
    in >> p;
    in >> t;
    int n = t.length();
    int m = p.length();
    for (int i = 0; i <= n - m; ++i) {
        if (p == t.substr(i, m)) {
            ans.push_back(i + 1);
        }
    }

    out << ans.size() << std::endl;
    for (auto& i : ans) {
        out << i << " ";
    }
    return 0;
}