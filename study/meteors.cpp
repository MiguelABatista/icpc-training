// https://www.spoj.com/problems/METEORS/
// https://youkn0wwho.academy/topic-list/parallel_binary_search

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MAX = 300'005;

// BIT com update em range
//
// Operacoes 0-based
// query(l, r) retorna a soma de v[l..r]
// update(l, r, x) soma x em v[l..r]
//
// Complexidades:
// build - O(n)
// query - O(log(n))
// update - O(log(n))

struct querry{
	ll l, r, val;
};

class BIT{
	ll bit[2][MAX+2];
	ll n;
public:
	BIT(ll n2, v64& v) {
		n = n2;
		for (ll i = 1; i <= n; i++)
			bit[1][min(n+1, i+(i&-i))] += bit[1][i] += v[i-1];
	}
	ll get(ll x, ll i) {
		ll ret = 0;
		for (; i; i -= i&-i) ret += bit[x][i];
		return ret;
	}
	void add(ll x, ll i, ll val) {
		for (; i <= n; i += i&-i) bit[x][i] += val;
	}
	ll get2(ll p) {
		return get(0, p) * p + get(1, p);
	}
	ll query(ll l, ll r) {
		return get2(r+1) - get2(l);
	}
	void update(ll l, ll r, ll x) {
		add(0, l+1, x), add(0, r+2, -x);
		add(1, l+1, -x*l), add(1, r+2, x*(r+1));
	}
	void update(querry q) {
		if(q.r < q.l){
			update(0, q.r, q.val);
			update(q.l, n-1, q.val);
		} else{
			update(q.l, q.r, q.val);
		}
	}
};



int main(){
    _;
	ll n, m; cin >> n >> m;

	map<ll, v64> mp;
	
	v64 bit_aux(m,0);
	BIT bit(m, bit_aux);
	v64 required(n);

	map<ll,v64> left;
	map<ll,v64> right;
	map<ll,v64> mid;
	map<ll,v64> ans;
	
	forn(i,0,n){
		left[0].push_back(i);
		right[n-1].push_back(i);
		mid[(n-1)/2].push_back(i);
		ans[INF].push_back(i);
	}
	forn(i,0,m){
		ll aux;
		cin >> aux;
		mp[aux].push_back(i);
	} 

	forn(i,0,n) cin >> required[i];

	ll q; cin >> q;

	vector<querry> querries(q);

	forn(i,0,q){
		cin >> querries[i].l;
		cin >> querries[i].r;
		cin >> querries[i].val;
	}

	ll pot2 = 1;
	while(pot2 <= q){
		pot2 *= 2;
		forn(i,0,q){
			bit.update(querries[i]);

		}
	}
    return 0;
}