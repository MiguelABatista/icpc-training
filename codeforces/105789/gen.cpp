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
    ll n = 10;
    ll p = uniform(0,10);
    ll h = uniform(80000,90000);
    
    cout << n << " " << p << " " << h << ln;

    forn(i,0,n){
        char c = "!*+++"[uniform(0,4)];
        cout << c << " ";
        if(c == '!'){
            cout << ln;
            continue;
        }
        cout << uniform(1,10) << ln;
    }
    return 0;
}