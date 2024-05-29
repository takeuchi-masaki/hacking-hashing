#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef unsigned long long ll;
// const ull MOD=100000000000009ULL; //runtime ~0.6s
// const ull MOD=10000000000000009ULL; //runtime ~4.4s
//const ull MOD=1000000000000000009ULL; //runtime ~2min
const ull MOD = 1000000007;
// const ull MOD = (1LL << 61) - 1;
int base = 331;
static constexpr ull mul(ull a, ull b) {
    __int128 res = __int128(a) * b;
    return res % MOD;
}
static constexpr ull add(ull a, ull b) {
    __int128 res = a + b;
    return res % MOD;
}

inline ull my_hash(string s) {
	// ull h=0; for(auto c:s) h=(h*base+c)%MOD; return h;
	ull h = 0;
	for (auto c : s) {
	   h = add(mul(h, base), c);
	}
	return h;
}

string gen_str(ull u) {
	string s; u=u*819039758391039471ULL+283958671940506ULL;
	while(u) s.push_back(u%26+'a'),u/=26; return s;
}
inline ull next_hash(ull u) {
	ull h=0;
	u=u*819039758391039471ULL+283958671940506ULL;
	while(u) {
	   h = add(mul(h, base), char(u % 26 + 'a'));
	   u /= 26;
	}
	// while(u) h=(h*base+(char(u%26+'a')))%MOD,u/=26;
	return h;
}
unordered_map<ull,pair<int,ull>> w;
int main() {
	ull sh=1,x=sh,y,p,q; int c0,c1;
	while(1) {
		ull u=x; int c=0;
		do u=next_hash(u),++c; while((u-sh)%100007);
		if(w.count(u)) {c0=c; c1=w[u].first; y=w[u].second; break;}
		w[u]=make_pair(c,x); x=u;
	}
	int g=min(c0,c1);
	c0-=g; c1-=g;
	while(c0--) {
	   p=x,x=next_hash(x);
	}
	while(c1--) {
	   q=y,y=next_hash(y);
	}
	while(x!=y) {
		p=x,x=next_hash(x),
		q=y,y=next_hash(y);
	}
	string a=gen_str(p),b=gen_str(q);
	cout<<"hash("<<a<<")="<<my_hash(a)<<"\n";
	cout<<"hash("<<b<<")="<<my_hash(b)<<"\n";
	cout << a << "\n" << b << "\n";
}
