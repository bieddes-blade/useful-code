#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int main() {
    map<char, int> m;
    set<char> s;

    string c;
    while (cin >> c) {
        for (char ch : c) {
            if (m.find(ch) == m.end()) {
                m[ch] = 1;
                s.insert(ch);
            } else {
                ++m[ch];
            }
        }
    }

    vector<char> f_char;
    vector<int> f_int;

    int mx = 0;

    for (char ch : s) {
        f_char.push_back(ch);
        f_int.push_back(m[ch]);
        mx = max(mx, m[ch]);
    }

    int n = static_cast<int>(f_char.size());

    while (mx > 0) {
        c = "";
        for (int i = 0; i < n; ++i) {
            if (f_int[i] >= mx) {
                c += '#';
            } else {
                c += ' ';
            }
        }
        cout << c << "\n";
        --mx;
    }

    for (int i = 0; i < n; ++i) {
        cout << f_char[i];
    }
}