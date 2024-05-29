#include <iostream>
#include <unordered_map>
#include <chrono>
#include <vector>
typedef long long ll;
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) { // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<class K, class V> using hashmap = unordered_map<K, V, custom_hash>;

int main() {
    custom_hash hasher{};
    vector<int> values = { 1, 0, 212 };
    for (auto v : values) {
        cout << hasher(v) << "\n";
    }
}
