#include <bits/stdc++.h>
using namespace std;

/*
    splitmix64 parameters
*/
constexpr uint64_t ADD = 0x9e3779b97f4a7c15;
constexpr uint64_t MULT1 = 0xbf58476d1ce4e5b9;
constexpr uint64_t MULT2 = 0x94d049bb133111eb;
constexpr uint64_t SHIFT1 = 30;
constexpr uint64_t SHIFT2 = 27;
constexpr uint64_t SHIFT3 = 31;
/*
    https://doi.org/10.1145/2714064.2660195
*/
constexpr uint64_t splitmix64(uint64_t x) {
    uint64_t z = x + ADD;
    z = (z ^ (z >> SHIFT1)) * MULT1;
    z = (z ^ (z >> SHIFT2)) * MULT2;
    return z ^ (z >> SHIFT3);
}

/*
    Find multiplicative inverse of odd `x`
    x * inv(x) = 1 MOD 2^64
    https://lemire.me/blog/2017/09/18/computing-the-inverse-of-odd-integers/
*/
constexpr uint64_t inv64(uint64_t x) {
    uint64_t y = (3 * x) ^ 2;
    for (int i = 0; i < 4; i++) {
        y *= 2 - y * x;
    }
    return y;
}

/*
    Reverse xorshift operation: x = x ^ (x >> shift)
    https://marc-b-reynolds.github.io/math/2017/10/13/IntegerBijections.html
*/
constexpr uint64_t rev_xorshift(uint64_t x, uint64_t shift) {
    while (shift < 64) {
        x = x ^ (x >> shift);
        shift *= 2;
    }
    return x;
}

constexpr uint64_t unmix64(uint64_t z) {
    z = rev_xorshift(z, SHIFT3);
    z *= inv64(MULT2);
    z = rev_xorshift(z, SHIFT2);
    z *= inv64(MULT1);
    z = rev_xorshift(z, SHIFT1);
    z -= ADD;
    return z;
}


int main() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

    vector<uint64_t> seeds = {
        0x1234567890123456,
        0x5ca1ab1ef005ba11,
        0xdeadbea7dad5,
        unmix64(0),
        unmix64(1),
        rng(),
        rng(),
        rng(),
    };

    cout << hex;
    for (auto seed : seeds) {
        auto mixed = splitmix64(seed);
        auto unmix = unmix64(mixed);
        cout << seed << "\n"
            << mixed << "\n"
            << unmix << "\n\n";
    }
}
