#include <algorithm>
#include <cassert>
#include <chrono>
#include <format>
#include <iostream>
#include <map>
#include <random>
#include <vector>
typedef long long ll;
using namespace std;

/*
    String matching test code using modulo (2^61 - 1) mersenne prime
*/
typedef uint64_t ull;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const ull BASE = uniform_int_distribution<>(258, int(2e9))(rng);
struct PolyHash {
    static constexpr ull MOD = (1ULL << 61) - 1;

    static inline ull add(ull a, ull b) {
        a += b;
        if (a >= MOD) a -= MOD;
        return a;
    }
    static inline ull sub(ull a, ull b) {
        a -= b;
        if (a >= MOD) a += MOD;
        return a;
    }
    static inline ull mul(ull a, ull b) {
        ull l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
        ull l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
        ull ret = (l & MOD) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
        ret = (ret & MOD) + (ret >> 61);
        ret = (ret & MOD) + (ret >> 61);
        return ret - 1;
    }

    vector<ull> power, pref;
    PolyHash(const string &s) : pref(s.length() + 1) {
        power = { 1 };
        while (power.size() <= s.length()) {
            power.push_back(mul(power.back(), BASE));
        }
        for (int i = 0; i < (int)s.length(); i++) {
            pref[i + 1] = add(mul(pref[i], BASE), s[i]);
        }
    }

    ull operator () (int pos, int len) const {
        return sub(pref[pos + len], mul(pref[pos], power[len]));
    }
};

/*
    solve problem:
    given two strings, a string `s` and a pattern string `t`,
    count the number of times the pattern string `t` matches a substring of string `s`
*/
void solve() {
    string s, t;
    cin >> s >> t;
    int n = int(s.size());
    PolyHash s_hash(s), t_hash(t);
    cout << s << " " << s_hash(0, n) << "\n"
        << t << " " << t_hash(0, n) << "\n";
}

int main() {
    solve();
}
