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
        a = -a;
        b = -b;
		auto x = insert({a, b, 0});
		while (overlap(x)) erase(next(x)), update(x);
		if (x != begin() and !overlap(prev(x))) x = prev(x), update(x);
		while (x != begin() and overlap(prev(x))) 
			x = prev(x), erase(next(x)), update(x);
	}
	
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
#warning cuidado com overflow!
		return -(l.a * x + l.b);
	}
};


int main(){
    _;
    ll n; ll c;
    cin >> n >> c;

    v64 vec(n);
    for(ll& x: vec) cin >> x;

    v64 dp(n, INF);
    CHT cht;
    cht.add(0,0);

    forn(i,0,n){
        cht.add(-2*vec[i], vec[i]*vec[i] + (i == 0 ? 0 : dp[i-1]));
        dp[i] = cht.query(vec[i]) + c + vec[i]*vec[i];
    }

    // forn(i,0,n) cout << dp[i] << ln;; cout << ln;
    cout << dp[n-1] << ln;
    return 0;
}