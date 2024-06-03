#include <bits/stdc++.h>
using namespace std;


/*
    find last bucket size
    primes dependent on compiler
*/
int find_size(int N) {
    unordered_set<int64_t> st;
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

void run(int N, int bucket_size) {
    unordered_map<int64_t, int64_t> mp;
    int64_t curr = 0;
    for (int i = 0; i < N; i++) {
        mp[curr]++;
        curr += bucket_size;
    }

    int64_t sum = 0;
    for (int i = 0; i < N; i++) {
        curr -= bucket_size;
        sum += mp[curr];
    }
    cout << sum << "\n";
}

int main() {
    const int N = int(1e5);
    int bucket_cnt = find_size(N);

    /* timing hashmap */
    auto start_time = chrono::steady_clock::now();

    /* run adversarial operation */
    run(N, bucket_cnt);

    auto end_time = chrono::steady_clock::now();
    cout << "\nruntime: " << fixed << setprecision(2)
        << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e6
        << " ms\n";
}