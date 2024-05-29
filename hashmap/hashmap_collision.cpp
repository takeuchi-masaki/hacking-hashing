#include <chrono>
#include <iomanip>
#include <iostream>
#include <unordered_map>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
    ll ret = a * b - M * ull(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
    ull ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1) ans = modmul(ans, b, mod);
    return ans;
}
bool isPrime(ull n) { // Miller-Rabin
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 },
        s = __builtin_ctzll(n - 1), d = n >> s;
    for (ull a : A) { // ^ count trailing zeroes
        ull p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = modmul(p, p, n);
        if (p != n - 1 && i != s) return 0;
    }
    return 1;
}

const int MAX = int(1e6);
const int N = int(2e5);

void insert_numbers(long long x) {
    auto start_time = chrono::steady_clock::now();

    unordered_map<long long, int> numbers;
    for (int i = 1; i <= N; i++) {
        numbers[i * x] = i;
    }
    long long sum = 0;
    for (auto& entry : numbers) {
        sum += (entry.first / x) * entry.second;
    }

    auto end_time = chrono::steady_clock::now();
    double elapsed = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e6;
    if (elapsed > 1000) {
        printf("x = %lld: %.3lf seconds, sum = %lld\n", x, elapsed, sum);
    }
}

int main() {
    // for (int num = 2; num < MAX; num++) {
    //     if (num % 10000 == 0) {
    //         cout << num << ":\n";
    //     }
    //     if (isPrime(num)) {
    //         insert_numbers(num);
    //     }
    // }
    insert_numbers(205759);
}
