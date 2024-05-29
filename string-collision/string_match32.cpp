#include <algorithm>
#include <cassert>
#include <chrono>
#include <format>
#include <iostream>
#include <map>
#include <random>
#include <vector>
typedef unsigned long long ll;
using namespace std;

/*
    String matching test code using 32 bit modulo
*/
int base = 331;
const ll MOD = 1000000007;
// const ll MOD = (1LL << 61) - 1;
struct mint {
    uint64_t val;
    mint() : val(0) {}
    mint(ll v) : val(((v % MOD) + MOD) % MOD) {}
    mint(ll a, ll b) : mint(a) { *this /= mint(b); } // a * b^-1
    mint& operator+=(mint const& b) { val += b.val; if (val >= MOD) val -= MOD; return *this; }
    mint& operator-=(mint const& b) { val += MOD - b.val; return *this; }
    mint& operator*=(mint const& b) { // kactl modmul
        int64_t res = this->val * b.val - MOD * uint64_t(1.L / MOD * this->val * b.val);
        val = res + MOD * (res < 0) - MOD * (res >= (int64_t)MOD); return *this;
    }
    friend mint mexp(mint b, ll e) { // kactl modpow binary exponentiation
        mint res(1); for (; e; b *= b, e /= 2) if (e & 1) res *= b; return res;
    }
    friend mint inverse(mint a) { return mexp(a, MOD - 2); } // assumes MOD is prime
    mint& operator/=(mint const& b) { return *this *= inverse(b); }
    friend mint operator+(mint a, mint const b) { return a += b; }
    friend mint operator-(mint a, mint const b) { return a -= b; }
    friend mint operator-(mint const a) { return 0LL - a; }
    friend mint operator*(mint a, mint const b) { return a *= b; }
    friend mint operator/(mint a, mint const b) { return a /= b; }
    friend ostream& operator<<(ostream& os, mint const& a) { return os << a.val; }
    friend bool operator==(mint const& a, mint const& b) { return a.val == b.val; }
    friend bool operator!=(mint const& a, mint const& b) { return a.val != b.val; }
};

mint compute_hash(const string& s, int len) {
    mint hash{};
    for (int i = 0; i < len; i++) {
        hash = (hash * base) + s[i];
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
    mint s_hash = compute_hash(s, n); // string hash
    mint t_hash = compute_hash(t, n); // pattern hash
    cout << s << "\t" << s_hash << "\n"
        << t << "\t" << t_hash << "\n";
    int ans = (s_hash == t_hash);
    // auto roll_hash = [&](int nxt_idx) {
    //     int prev_idx = nxt_idx - m;
    //     s_hash -= s[prev_idx] * pows[0];
    //     s_hash += s[nxt_idx] * pows[m];
    //     s_hash /= base;
    // };
    // for (int nxt = m; nxt < n; nxt++) {
    //     roll_hash(nxt);
    //     ans += (s_hash == t_hash);
    // }
    cout << ans << endl;
}

int main() {
    solve();
}
