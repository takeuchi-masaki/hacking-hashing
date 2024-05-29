#include <bits/stdc++.h>
using namespace std;

int main() {
    for (int i = 0; i < 100; i++) {
        auto time = chrono::steady_clock::now().time_since_epoch().count();
        cout << time << "\n";
    }
}
