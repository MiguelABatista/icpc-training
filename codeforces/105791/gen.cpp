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

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}

int main(){
    _;
	ll t = uniform(1000000, 1000000);
	cout << t << ln;
	forn(i, 0 ,t) {
		ll a = uniform(1, 1'000'000'000'000'000'0ll);
		ll b = uniform(1, 1'000'000'000'000'000'0ll);
		if (a > b) swap(a, b);
		cout << a << " " << b << ln;
	}

    return 0;
}