#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MAX = 300'000;

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
};

int main(){
    _;
    v64 v = {1, 2 , 0 , -1 , 2 , 3};
    BIT b(v.size(), v);

    cout << b.query(1,3) << ln;
    cout << b.query(2,3) << ln;
    cout << b.query(1,4) << ln;
    return 0;
}