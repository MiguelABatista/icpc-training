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

const ll MAXA = 10;

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}

void solve(){
    ll n = 5; ll q = 5;
    cout << n << ' ' << q << ln;
    forn(i,0,n) cout << uniform(1, MAXA) << " ";
    cout << ln;
    forn(i,0,q){
        ll t = uniform(1,2);
        cout << t << " ";
        if(t == 2) cout << uniform(1,n) << ln;
        else cout << uniform(1,MAXA) << " " << uniform(1,MAXA) << ln;
    }
}

int main(){
    _;
    ll t = 1;
    cout << t << ln;
    while(t--){
        solve();
    } 
}