#include <vector>
#include <iostream>

using namespace std;

struct Query {
    int value;
    int prev;
};

vector<Query> s;

void push(int i, int x) {
    Query add;
    add.value = x;
    add.prev = i;
    s.resize(s.size() + 1);
    s[s.size() - 1] = add;
}

int pop(int i) {
    Query del = s[i - 1];
    del = s[del.prev - 1];
    push(del.prev, del.value);
    return s[i - 1].value;
}

int main() {
    freopen("0", "r", stdin);

    push(0, 0);

    push(1, 1);
    push(2, 5);
    push(3, 4);
    push(4, 2);
    push(5, 3);
    pop(6);
    push(7, 6);
    pop(2);

    
    for (auto i : s) {
        cout << i.value << " " << i.prev << "\n";
    }
    cout << "\n";

    return 0;
}