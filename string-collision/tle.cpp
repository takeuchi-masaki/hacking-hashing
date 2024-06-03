#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef unsigned long long ll;

/*
space Floyd Cycle-finding algorithm
https://codeforces.com/blog/entry/60442?#comment-579029
*/
// constexpr ull MOD=100000000000009ULL; //runtime ~0.6s
// constexpr ull MOD = 10000000000000009ULL; //runtime ~4.4s
// constexpr ull MOD=1000000000000000009ULL; //runtime ~2min
// constexpr ull MOD = 1000000007;
// const ull MOD = (1LL << 61) - 1;
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
constexpr int base = 331;

constexpr uint64_t MOD = (1LL << 61) - 1;
typedef struct mint61 {
    uint64_t val;
    constexpr mint61() : val(0) {}
    constexpr mint61(int64_t v) : val((v + MOD) % MOD) {}
    constexpr mint61(int64_t a, int64_t b) : mint61(a) { *this /= mint61(b); } // a * b^-1
    constexpr mint61& operator+=(mint61 const& b) { val += b.val; if (val >= MOD) val -= MOD; return *this; }
    constexpr mint61& operator-=(mint61 const& b) { val += MOD - b.val; if (val >= MOD) val -= MOD; return *this; }
    constexpr mint61& operator*=(mint61 const& b) {
        uint64_t l1 = (uint32_t)val, h1 = val >> 32, l2 = (uint32_t)b.val, h2 = b.val >> 32;
        uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
        val = (l & MOD) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
        val = (val & MOD) + (val >> 61); val = (val & MOD) + (val >> 61); val--;
        return *this;
    }
    friend constexpr mint61 mexp(mint61 b, int64_t e) { mint61 res(1); for (; e; b *= b, e /= 2) if (e & 1) res *= b; return res; }
    friend constexpr mint61 inverse(mint61 a) { return mexp(a, MOD - 2); } // assumes a, MOD coprime
    constexpr mint61 operator/=(mint61 const& b) { return *this *= inverse(b); }
    friend constexpr mint61 operator+(mint61 a, mint61 const b) { return a += b; }
    friend constexpr mint61 operator-(mint61 a, mint61 const b) { return a -= b; }
    friend constexpr mint61 operator-(mint61 const a) { return 0 - a; }
    friend constexpr mint61 operator*(mint61 a, mint61 const b) { return a *= b; }
    friend constexpr mint61 operator/(mint61 a, mint61 const b) { return a /= b; }
    friend constexpr istream& operator>>(istream& is, mint61& a) { int64_t in; is >> in; a = mint61(in); return is; }
    friend constexpr ostream& operator<<(ostream& os, mint61 const& a) { return os << a.val; }
    friend constexpr bool operator==(mint61 const& a, mint61 const& b) { return a.val == b.val; }
    friend constexpr bool operator!=(mint61 const& a, mint61 const& b) { return a.val != b.val; }
} mint;

constexpr ull compute_hash(string s) {
    mint h;
    for (auto c : s) {
        h = h * base + c;
    }
    return h.val;
}
constexpr string gen_str(ull u) {
    string s; u = u * 819039758391039471ULL + 283958671940506ULL;
    while (u) s.push_back(u % 26 + 'a'), u /= 26; return s;
}
constexpr ull next_hash(ull u) {
    mint h;
    u = u * 819039758391039471ULL + 283958671940506ULL;
    while (u) {
        h = h * base + char(u % 26 + 'a');
        u /= 26;
    }
    return h.val;
}

unordered_map<ull, pair<int, ull>> w;
void run() {
    ull sh = 1, x = sh, y, p, q;
    int c0, c1;
    while (1) {
        ull u = x; int c = 0;
        do {
            u = next_hash(u);
            ++c;
        } while ((u - sh) % 100007);
        if (w.count(u)) {
            c0 = c;
            c1 = w[u].first; y = w[u].second;
            break;
        }
        w[u] = make_pair(c, x); x = u;
    }
    int g = min(c0, c1);
    c0 -= g;
    c1 -= g;
    while (c0--) {
        p = x, x = next_hash(x);
    }
    while (c1--) {
        q = y, y = next_hash(y);
    }
    while (x != y) {
        p = x, x = next_hash(x);
        q = y, y = next_hash(y);
    }
    string a = gen_str(p), b = gen_str(q);
    cout << "hash(" << a << ")=" << compute_hash(a) << "\n";
    cout << "hash(" << b << ")=" << compute_hash(b) << "\n";
    cout << a << "\n" << b << "\n";
}

int main() {
    auto start_time = chrono::steady_clock::now();
    run();
    auto end_time = chrono::steady_clock::now();
    cout << "\nruntime: " << fixed << setprecision(2)
        << chrono::duration_cast<chrono::seconds>(end_time - start_time).count()
        << " sec\n";
}
