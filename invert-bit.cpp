#include <vector>
#include <iostream>

using namespace std;

int main() {
    int mask, place;
    cin >> mask >> place;

    int size = 0, t = mask;
    while (t > 0) {
        t /= 2;
        ++size;
    }

    int n = mask & (1 << place), ans = 0;

    for (int i = 0; i < place; ++i) {
        ans |= mask & (1 << i);
    }

    if (n == 0) {
        ans |= (1 << place);
    }

    for (int i = place + 1; i < size; ++i) {
        ans |= mask & (1 << i);
    }

    cout << ans;
}