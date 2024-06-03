#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = int(1e5);

/*
    find last bucket size
    primes dependent on compiler
*/
int find_size() {
    unordered_set<ll> st;
    vector<uint32_t> prev;
    for (int i = 0; i < N; i++) {
        st.insert(i);
        if (prev.empty() || st.bucket_count() != prev.back()) {
            prev.push_back(st.bucket_count());
            cout << st.size() << ": " << prev.back() << "\n";
        }
    }
    return prev.back();
}

vector<ll> get_values(int prev) {
    vector<ll> to_add;
    int curr = 0;
    while (to_add.size() < N) {
        to_add.push_back(curr);
        curr += prev;
    }
    return to_add;
}

void run(vector<ll>& to_add) {
    unordered_map<ll, ll> mp;
    for (int i = 0; i < N; i++) {
        mp[to_add[i]] = i;
    }
    ll sum = 0;
    for (auto x : to_add) {
        sum += mp[x];
    }
    cout << sum << "\n";
}

int main() {
    int bucket_cnt = find_size();
    vector<ll> to_add = get_values(bucket_cnt);

    /* timing operations */
    auto start_time = chrono::steady_clock::now();

    /* run adversarial operation */
    run(to_add);

    auto end_time = chrono::steady_clock::now();
    cout << "\nruntime: " << fixed << setprecision(2)
        << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e6
        << " ms\n";
}