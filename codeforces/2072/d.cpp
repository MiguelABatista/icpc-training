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

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    vector<p64> delta(n);
    forn(i,0,n) cin >> vec[i];

    ll inv;
    ll eq;
    ll best_delta;
    ll best_r;
    forn(i,0,n){
        inv = 0;
        eq = 0;
        best_delta = 0;
        best_r = i;
        forn(j,i+1,n){ 
            if(vec[i] > vec[j]) inv++;
            if(vec[i] == vec[j]) eq++;
            ll inv_pos = (j-i) - inv - eq;
            debug(inv_pos);
            debug(inv);
            if(best_delta > inv_pos - inv){
                best_delta = inv_pos - inv;
                best_r = j;
            }
        }
        delta[i] = {best_delta, best_r};
        debug(1);
    }

    // forn(i,0,n){
    //     cout << delta[i].first << ' ' << delta[i].second << ln;
    // }

    ll l_ans, r_ans, delta_ans;
    delta_ans = INF;
    forn(i,0,n){
        if(delta[i].first < delta_ans){
            l_ans = i;
            r_ans = delta[i].second;
            delta_ans = delta[i].first;
        }
    }

    // cout << calc_inv(vec) + delta_ans << ln;
    cout << l_ans+1 << ' ' << r_ans+1 << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}