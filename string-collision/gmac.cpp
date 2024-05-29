#include <stdint.h>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
typedef unsigned __int128 u128;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

u128 compute_hash(std::string& s, int base) {
    u128 hash = 0;
    for (char c : s) {
        hash *= base;
        hash += c;
    }
    return hash;
}

std::string to_string(u128 num) {
    std::string s;
    while (num > 0) {
        s.push_back((num % 10) + '0');
        num /= 10;
    }
    std::reverse(s.begin(), s.end());
    return s;
}

bool run(int Q) {
    int base = std::uniform_int_distribution<>(256, int(1e9))(rng) | 1;
    int N = 1 << Q;
    std::string S(N, ' '), T(N, ' ');
    for (int i = 0; i < N; i++) {
        S[i] = 'A' + __builtin_popcount(i) % 2;
    }
    for (int i = 0; i < N; i++) {
        T[i] = 'B' - __builtin_popcount(i) % 2;
    }
    u128 hash1 = compute_hash(S, base);
    u128 hash2 = compute_hash(T, base);
    return hash1 == hash2;
}

int main() {
    const int TEST_CNT = 1000;
    std::cout << std::setprecision(2) << std::fixed;
    for (int q = 2; q < 20; q++) {
        int collide = 0;
        for (int t = 0; t < TEST_CNT; t++) {
            collide += run(q);
        }
        std::cout << "Q: " << q << '\t'
            << double(collide) / TEST_CNT << "\n";
    }
}
