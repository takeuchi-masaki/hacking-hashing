#include <bits/stdc++.h>
using namespace std;

typedef uint64_t ll;
static constexpr ll MOD = (1LL << 61) - 1;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll base = uniform_int_distribution<ll>(300, (1e9) + 7)(rng);
static constexpr ll add(ll a, ll b) {
    a += b;
    if (a > MOD) a -= MOD;
    return a;
}
static constexpr ll sub(ll a, ll b) {
    return add(a, MOD - b);
}
static constexpr ll mul(ll a, ll b) {
    ll l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
    ll l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    ll ret = (l & MOD) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & MOD) + (ret >> 61);
    ret = (ret & MOD) + (ret >> 61);
    return ret - 1;
}

class Solution {
public:
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        for (auto& p : pattern) p += 2; // {-1, 0, 1} -> {1, 2, 3}
        ll p_hash = 0;
        for (auto p : pattern) {
            p_hash = mul(p_hash, base);
            p_hash = add(p_hash, p);
        }
        auto comp = [](int a, int b) -> int{
            if (b > a) return 3;
            if (b == a) return 2;
            return 1;
        };
        ll hash = 0, mult = 1;
        for (int i = 1; i <= pattern.size(); i++) {
            hash = mul(hash, base);
            hash = add(hash, comp(nums[i - 1], nums[i]));
            mult = mul(mult, base);
        }
        int ans = (hash == p_hash);
        for (int i = pattern.size() + 1; i < nums.size(); i++) {
            hash = mul(hash, base);
            hash = add(hash, comp(nums[i - 1], nums[i]));
            hash = sub(hash, mul(comp(nums[i - pattern.size() - 1], nums[i - pattern.size()]), mult));
            ans += (hash == p_hash);
        }
        return ans;
    }
};
