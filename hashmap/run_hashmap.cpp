#include <bits/stdc++.h>
#include <chrono>
using namespace std;

void run() {
    int n;
    cin >> n;
    vector<int> A(n);
    for (auto& a : A) cin >> a;

    unordered_map<int, int> M;
    for (auto a : A) {
        M[a]++;
    }
    long long sum = 0;
    for (auto a : A) {
        sum += M[a];
    }
    cout << "output: ";
    cout << sum << "\n";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    auto start = chrono::steady_clock::now();
    run();
    auto end = chrono::steady_clock::now();
    double ms = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1e6;
    cout << fixed << setprecision(2) << ms << "ms\n";
}
