#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(a, b) uniform_int_distribution<ull>(a, b)(rng)

constexpr int MOD = 1000000007;
typedef struct mint32 {
    uint64_t val;
    constexpr mint32() : val(0) {}
    constexpr mint32(int64_t v) : val((v + MOD) % MOD) {}
    constexpr mint32(int64_t a, int64_t b) : mint32(a) { *this /= mint32(b); } // a * b^-1
    constexpr mint32& operator+=(mint32 const& b) { val += b.val; if (val >= MOD) val -= MOD; return *this; }
    constexpr mint32& operator-=(mint32 const& b) { val += MOD - b.val; if (val >= MOD) val -= MOD; return *this; }
    constexpr mint32& operator*=(mint32 const& b) { val = (val * b.val) % MOD; return *this; }
    friend constexpr mint32 mexp(mint32 b, int64_t e) { mint32 res(1); for (; e; b *= b, e /= 2) if (e & 1) res *= b; return res; }
    friend constexpr mint32 inverse(mint32 a) { return mexp(a, MOD - 2); } // assumes a, MOD coprime
    constexpr mint32& operator/=(mint32 const& b) { return *this *= inverse(b); }
    friend constexpr mint32 operator+(mint32 a, mint32 const b) { return a += b; }
    friend constexpr mint32 operator-(mint32 a, mint32 const b) { return a -= b; }
    friend constexpr mint32 operator-(mint32 const a) { return 0 - a; }
    friend constexpr mint32 operator*(mint32 a, mint32 const b) { return a *= b; }
    friend constexpr mint32 operator/(mint32 a, mint32 const b) { return a /= b; }
    friend constexpr istream& operator>>(istream& is, mint32& a) { int64_t in; is >> in; a = in; return is; }
    friend constexpr ostream& operator<<(ostream& os, mint32 const& a) { return os << a.val; }
    friend constexpr bool operator==(mint32 const& a, mint32 const& b) { return a.val == b.val; }
    friend constexpr bool operator!=(mint32 const& a, mint32 const& b) { return a.val != b.val; }
} mint;

ull compute_hash(string& s, ull base) {
    mint hash{};
    for (char c : s) {
        hash = hash * base + c;
    }
    return hash.val;
}
string get_string(ull value, int length) {
    string res{};
    for (int ch = 0; ch < length; ch++) {
        res.push_back('a' + (value % 26));
        value /= 26;
    }
    return res;
}
string get_string2(ull value, int length) {
    string res{};
    for (int bit = 0; bit < length; bit++) {
        res.push_back('a' + (value >> bit & 1));
    }
    return res;
}

/*
generate random strings of lowercase letters
64 bit random number -> 26^length
*/
void test(ull base, int length) {
    ull MAX_VALUE = 1;
    for (int i = 0; i < length; i++) {
        ull nxt = MAX_VALUE * 26;
        if (nxt < MAX_VALUE) {
            // overflowed
            cerr << "length too long for random\n";
            abort();
        }
        MAX_VALUE = nxt;
    }

    cout << "BASE: " << base << "\tLENGTH: " << length << '\n';
    const int MAX_TESTS = int(1e5); // 1e5 * 1e5 > MOD
    unordered_map<ull, ull> M;
    for (int t = 0; t < MAX_TESTS; t++) {
        ull mask = uid(0, MAX_VALUE);
        string str1 = get_string(mask, length);
        ull hash = compute_hash(str1, base);
        auto it = M.find(hash);
        if (it == M.end()) {
            M[hash] = mask;
            continue;
        }
        if (it->second == mask) {
            // prng generated duplicate bitmask
            continue;
        }
        // else: collision found
        cout << "COLLISION FOUND: " << t << " compared\n";
        string str2 = get_string(it->second, length);
        cout << str1 << "\t" << compute_hash(str1, base) << "\n";
        cout << str2 << "\t" << compute_hash(str2, base) << "\n";
        return;
    }
    cout << "NO COLLISIONS FOUND\n";
}

/*
generate all 2^n strings with only 'a' and 'b's, of length n
*/
void test_iter(int base, int length) {
    assert(length < 25);
    cout << "BASE: " << base << "\tLENGTH: " << length << '\n';
    cout << "CHECKING ITERATIVELY\n";
    unordered_map<ull, ull> M;
    const int MAX_MASK = 1 << length;
    for (int mask = 0; mask < MAX_MASK; mask++) {
        string str1 = get_string2(mask, length);
        ull hash = compute_hash(str1, base);
        auto it = M.find(hash);
        if (it == M.end()) {
            M[hash] = mask;
            continue;
        }
        // else: collision found
        cout << "COLLISION FOUND:\n";
        string str2 = get_string2(it->second, length);
        cout << str1 << "\t" << compute_hash(str1, base) << "\n";
        cout << str2 << "\t" << compute_hash(str2, base) << "\n";
        return;
    }
    cout << "NO COLLISIONS FOUND\n";
}

int main() {
    test(331, 15);
    // test_iter(331, 20);
}
