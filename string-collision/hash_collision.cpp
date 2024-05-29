#include <bits/stdc++.h>
using namespace std;
#include <debugoutput.h>
typedef long long ll;
[[maybe_unused]] constexpr int INF = 0x3f3f3f3f;
[[maybe_unused]] constexpr ll LINF = 0x3f3f3f3f3f3f3f3f;
template<class T> bool chmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool chmax(T& a, const T& b) { return b > a ? a = b, 1 : 0; }
#define rep(i, a, b) for (int i = int(a), i##_max_ = int(b); i < i##_max_; i++)
#define rrep(i, a, b) for (int i = int(a), i##_min_ = int(b); i >= i##_min_; i--)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define len(x) (int)(x).size()
#define vec vector
#define pii pair<ll, ll>

using ll = long long;

const int MOD = 1000000007;
struct mint { // modular int: assumes initial input fits int64
    uint64_t val;
    mint() : val(0) {}
    mint(ll v) : val((v + MOD) % MOD) {}
    mint(ll a, ll b) : val(a) { *this /= mint(b); } // a * b^-1
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

const int MX_len = int(2e5) + 5;
vector<mint> pows;
void init(ll base) {
    pows.clear();
    mint curr(1);
    for (int i = 1; i < MX_len; i++) {
        pows.push_back(curr);
        curr *= base;
    }
}

#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng) // [a, b]
mt19937_64 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

void print_binary(ll value, int length) {
    cout << "{ ";
    rrep(bit, length - 1, 0) {
        cout << (value >> bit & 1) << ", ";
    }
    cout << "}\n";
}

void test(ll base, int length) {
    cout << "BASE: " << base << "\tLENGTH: " << length << '\n';
    init(base);

    const int TEST_CNT = int(1e5);
    map<ll, ll> prev;
    rep(t, 0, TEST_CNT) {
        ll mask = uid(0, (1LL << length) - 1);
        mint nxt_hash(0);
        rep(bit, 0, length) {
            nxt_hash += ((mask >> bit & 1) + 1) * pows[bit];
        }
        if (prev.count(nxt_hash.val) && prev[nxt_hash.val] != mask) {
            cout << "COLLISION\n";
            dbg(prev[nxt_hash.val], mask);
            print_binary(prev[nxt_hash.val], length);
            print_binary(mask, length);
            return;
        }
        prev[nxt_hash.val] = mask;
    }
    cout << "NO COLLISIONS FOUND\n";
}

void test_iter(int base, int length) {
    assert(length < 25);
    cout << "BASE: " << base << "\tLENGTH: " << length << '\n';
    init(base);

    map<ll, ll> prev;
    rep(mask, 0, (1 << length)) {
        mint nxt_hash(0);
        rep(bit, 0, length) {
            nxt_hash += ((mask >> bit & 1) + 1) * pows[bit];
        }
        if (!prev.count(nxt_hash.val)) {
            prev[nxt_hash.val] = mask;
            continue;
        }

        cout << "COLLISION\n";
        print_binary(prev[nxt_hash.val], length);
        print_binary(mask, length);
        return;
    }
    cout << "NO COLLISIONS FOUND\n";
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    ll base = uid(2, MOD - 1);
    test(base, 24);
}
