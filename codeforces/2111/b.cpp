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
vector<ll> fib = {1,2,3,5,8,13,21,34,55,89};

void solve(){
    ll n, m; cin >> n >> m;
    vector<pair<p64, ll>> box;

    forn(i,0,m){
        ll w,l, h;
        cin >> w >> l >> h;
        if(l > w) swap(w,l);
        if(h > w) swap(w,h);
        if(h > l) swap(l,h); 

        debug(w);
        debug(l);
        debug(h);
        debug(fib[n-1]);

        if(fib[n-1] > h){
            cout << 0;
            continue;
        }
        if(fib[n-1]+fib[n-2] > w){
            cout << 0;
            continue;
        }
        cout << 1;
    }

    cout << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}