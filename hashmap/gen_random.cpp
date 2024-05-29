#include <iostream>
#include <chrono>
#include <random>
using namespace std;


const int MAX_VAL = int(1e9);
const int MAX_SIZE = int(1e5);

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> uid(0, MAX_VAL);

    vector<int> res;
    for (int i = 0; i < MAX_SIZE; i++) {
        res.push_back(uid(rng));
    }

    cout << res.size() << "\n";
    for (auto num : res) {
        cout << num << " ";
    }
    cout << "\n";
}
