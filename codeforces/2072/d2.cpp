#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll calc_inv(v64 &v){
    ll n = v.size();
    ll resp = 0;
    forn(i,0,n){
        forn(j,i+1,n){
            if(v[i] > v[j]) resp++;
        }
    }
    return resp;
}

ll testa(ll l, ll r, v64 vec){
    ll vl = vec[l];
    forn(i,l,r){
        vec[i] = vec[i+1];
    }
    vec[r] = vl;
    return calc_inv(vec);
}

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    ll best_l;
    ll best_r;
    ll best_v = INF;

    forn(l,0,n){
        forn(r,l,n){
            ll v = testa(l,r,vec);
            if(v < best_v){
                best_l = l;
                best_v = v;
                best_r = r;
            }
        }
    }
    cout << best_l << ' ' << best_r << ln;
    cout << best_v << ln;
}


int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}