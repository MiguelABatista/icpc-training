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

const ll maxv = 1000100;

int main(){
    _;
    ll n; cin >> n;
	v64 foods(n);
	v64 people(n);

	v64 pow2(maxv);
    pow2[1] = 2;
    forn(i, 2, maxv) {
        pow2[i] = (pow2[i-1] * 2) % (1'000'000'000 + 7);
    }
    forn(i, 0, n) cin >> foods[i];
	ll q; cin >> q;
    
	forn(j,0, q){
		ll p; cin >> p;

		ll counter = 0;

		forn(i,0,n){
			if( gcd(p,foods[i]) == 1) counter++;
		}

		cout << pow2[counter] << ln;
	}
 
    return 0;
}