#include <algorithm>
#include <cassert>
#include <chrono>
#include <format>
#include <iostream>
#include <map>
#include <random>
#include <vector>
using namespace std;

/*
    String matching test code using 64 bit modulo
*/
static constexpr uint64_t MOD = (1LL << 61) - 1;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int base = uniform_int_distribution<int>(2, int(1e9))(rng);
static inline constexpr uint64_t add(uint64_t a, uint64_t b) {
    return ((a += b) >= MOD ? a -= MOD : a);
}
static inline constexpr uint64_t sub(uint64_t a, uint64_t b) {
    return add(a, MOD - b);
}
static inline constexpr uint64_t mul(uint64_t a, uint64_t b) {
	int64_t ret = a * b - MOD * uint64_t(1.L / MOD * a * b);
	return ret + MOD * (ret < 0) - MOD * (ret >= MOD);
}
// static inline constexpr uint64_t mul(uint64_t a, uint64_t b) {
//     uint64_t l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
//     uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
//     uint64_t ret = (l & MOD) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
//     ret = (ret & MOD) + (ret >> 61);
//     ret = (ret & MOD) + (ret >> 61);
//     return ret - 1;
// }
uint64_t compute_hash(string& s, int len) {
    uint64_t hash = 0;
    for (int i = 0; i < len; i++) {
        hash = add(mul(hash, base), s[i]);
    }
    return hash;
}

/*
    solve problem:
    given two strings, a string `s` and a pattern string `t`,
    count the number of times the pattern string `t` matches a substring of string `s`
*/
void solve() {
    string s, t;
    cin >> s >> t;
    int n = int(s.size());
    int m = int(t.size());
    assert(n >= m);
    uint64_t p_hash = compute_hash(t, m); // pattern hash
    uint64_t s_hash = compute_hash(s, m); // string hash
    int ans = (s_hash == p_hash);
    uint64_t pow = 1;
    for (int i = 0; i < m; i++) {
        pow = mul(pow, base);
    }
    for (int nxt = m; nxt < n; nxt++) {
        s_hash = sub(add(mul(s_hash, base), s[nxt]), mul(pow, s[nxt - m]));
        ans += (s_hash == p_hash);
    }
    cout << t << " " << p_hash << "\n"
        << s << " " << s_hash << "\n";
    cout << ans << endl;
}

int main() {
    solve();
}
