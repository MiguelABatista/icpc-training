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

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}


int main(){
    _;
    ll n = 10; 


    set<p64> s;
    forn(i,0,n-1){
        ll deg = uniform(0,3);
        forn(j,0,deg){
            s.insert({i+1, min(n, i+1 + uniform(1,3))});
        }
    }

    cout << n << " " << sz(s) << " " << 1 << ln;
    for(auto [a,b] : s){
        cout << a << " " << b << " " << uniform(1,10) << ln;
    }

    cout << uniform(1,n) << " " << uniform(1,n) << ln;

    return 0;
}