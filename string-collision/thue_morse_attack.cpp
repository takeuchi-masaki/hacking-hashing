#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(a, b) uniform_int_distribution<uint64_t>(a, b)(rng)

/* run thue morse sequence for up to max length, print results */
uint64_t compute_hash(string& s, uint64_t base) {
    uint64_t hash = 0;
    for (char c : s) {
        hash = hash * base + c;
        // if (c == 'A') {
        //     hash -= 1;
        // } else {
        //     hash += 1;
        // }
    }
    return hash;
}

void run(int q, uint64_t base) {
    int n = 1 << q;
    string s, t;
    char ch[] = {'A', 'Q'};
    for (int i = 0; i < n; i++) {
        s.push_back(ch[__builtin_parity(i)]);
        t.push_back(ch[!__builtin_parity(i)]);
    }
    uint64_t hash = compute_hash(s, base);
    uint64_t hash2 = compute_hash(t, base);
    cout << q << " " << n << "\n"
        << hash << "\n"
        << hash2 << "\n\n";
}

int main() {
    uint64_t base = uid(260, LLONG_MAX / 2) | 1;
    // uint64_t base = 333;
    for (int q = 1; q < 20; q++) {
        run(q, base);
    }
}
