#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

const __int128 p = 127, m = 18014398241046527;

int n;
string s;
vector<__int128> power, hashes;

__int128 num(char c) { return c - 'a' + 1; }

void count_hashes() {
    power.resize(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        power[i] = (power[i - 1] * p) % m;  
    }
    hashes.resize(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        hashes[i] = (hashes[i - 1] * p + num(s[i - 1])) % m;
    }
}

bool compare_str(int a, int b, int c, int d) {
    if (b - a != d - c) {
        return false;
    } else {
        __int128 hash_a = (hashes[b + 1] - hashes[a] * power[b - a + 1] % m + m) % m;
        __int128 hash_b = (hashes[d + 1] - hashes[c] * power[d - c + 1] % m + m) % m;
        if (a == c || hash_a == hash_b) {
            return true;
        } else {
            return false;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("0", "r", stdin);
    
    cin >> s;
    n = s.length();
        
    int queries, a, b, c, d;
    cin >> queries;

    count_hashes();
    
    for (int i = 0; i < queries; ++i)
    {
        cin >> a >> b >> c >> d;

        if (s[a] == s[c]) { // если первые символы строк равны
            int l = 0, r = min(b - a + 1, d - c + 1), m;
            while (l + 1 < r) {
                m = (l + r) / 2;
                if (compare_str(a, a + m, c, c + m)) {
                    l = m;
                } else {
                    r = m;
                }
            }

            if (l >= b - a && l >= d - c) { // если строки равны
                cout << "0\n";
            }

            else if (l >= b - a) { // если первая строка - префикс второй
                cout << "-1\n";
            }

            else if (l >= d - c) { // если вторая строка - префикс первой
                cout << "1\n";
            }

            else if (s[a + l + 1] < s[c + l + 1]) { // если первый символ после равного префикса меньше
                cout << "-1\n";
            }

            else { // если первый символ после равного префикса больше
                cout << "1\n";
            }

        } else if (s[a] < s[c]) { // если самый первый символ меньше
            cout << "-1\n";

        } else { // если самый первый символ больше
            cout << "1\n";
        }
    }
    
    return 0;
}
