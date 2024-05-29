#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = int(1e5);

/*
    find last two bucket sizes
    primes dependent on compiler
*/
pair<int, int> find_sizes() {
    unordered_set<ll> st;
    uint32_t prev1 = -1, prev2 = -1;
    for (int i = 0; i < N; i++) {
        st.insert(i);
        if (st.bucket_count() != prev1) {
            prev2 = std::move(prev1);
            prev1 = st.bucket_count();
            cout << st.size() << ": " << prev1 << "\n";
        }
    }
    return { prev2, prev1 };
}

vector<ll> get_values(int prev1, int prev2) {
    ll a = prev1, b = prev2;
    vector<ll> to_add;
    while (a < b && to_add.size() < N) {
        to_add.push_back(a);
        a += prev1;
    }
    while (to_add.size() < N) {
        to_add.push_back(a);
        a += prev1;
        if (to_add.size() >= N) break;
        to_add.push_back(b);
        b += prev2;
    }
    return to_add;
}

vector<ll> get_values(int prev) {
    vector<ll> to_add;
    int curr = prev;
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
    pair<int, int> bucket_cnt = find_sizes();
    cout << "bucket sizes: " << bucket_cnt.first << " " << bucket_cnt.second << "\n";
    vector<ll> to_add = get_values(bucket_cnt.first, bucket_cnt.second);
    // vector<ll> to_add = get_values(bucket_cnt.second);

    /* timing operations */
    auto start_time = chrono::steady_clock::now();
    /* run adversarial operation */
    run(to_add);
    auto end_time = chrono::steady_clock::now();
    cout << "\nruntime: " << fixed << setprecision(2)
        << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e6
        << " ms\n";
}