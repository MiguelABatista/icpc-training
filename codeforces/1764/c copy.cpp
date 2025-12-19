#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Convex Hull Trick Dinamico
//
// para double, use INF = 1/.0, div(a, b) = a/b
// update(x) atualiza o ponto de intersecao da reta x
// overlap(x) verifica se a reta x sobrepoe a proxima
// add(a, b) adiciona reta da forma ax + b
// query(x) computa maximo de ax + b para entre as retas
//
// O(log(n)) amortizado por insercao
// O(log(n)) por query

struct Line {
	mutable ll a, b, p;
	bool operator<(const Line& o) const { return a < o.a; }
	bool operator<(ll x) const { return p < x; }
};

struct CHT : multiset<Line, less<>> {
	ll div(ll a, ll b) { 
		return a / b - ((a ^ b) < 0 and a % b);
	}
	
	void update(iterator x) {
		if (next(x) == end()) x->p = INF;
		else if (x->a == next(x)->a) x->p = x->b >= next(x)->b ? INF : -INF;
		else x->p = div(next(x)->b - x->b, x->a - next(x)->a);
	}

	bool overlap(iterator x) {
		update(x);
		if (next(x) == end()) return 0;
		if (x->a == next(x)->a) return x->b >= next(x)->b;
		return x->p >= next(x)->p;
	}
		
	void add(ll a, ll b) {
		auto x = insert({a, b, 0});
		while (overlap(x)) erase(next(x)), update(x);
		if (x != begin() and !overlap(prev(x))) x = prev(x), update(x);
		while (x != begin() and overlap(prev(x))) 
			x = prev(x), erase(next(x)), update(x);
	}
	
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.a * x + l.b;
	}
};

void solve(){
    ll n; cin >> n;
    map<ll,ll> freq;
    forn(i,0,n) {
        ll x; cin >> x; 
        freq[x]++;
    }
    n = sz(freq);
    v64 vec(n);
    v64 acc(n);

    ll idx = 0;
    for(auto[k,v]:freq) vec[idx++] = v;
    acc[0] = vec[0];
    forn(i,1,n) acc[i] = acc[i-1] + vec[i];
    
    v64 dp(n);
    CHT cht;   
    cht.add(0, 0);

    forn(i,0,n){
        dp[i] = vec[i]/2 + (i == 0 ? 0 : dp[i-1]);
        ll aux = cht.query(vec[i]);
        dp[i] = max(dp[i],  aux + (i == 0? 0 : acc[i-1]*vec[i]));
        cht.add(-acc[i], dp[i]);
    }
    debugv(dp);
    cout << dp.back() << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}