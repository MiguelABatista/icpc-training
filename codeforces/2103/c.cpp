#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

p64 func(v64& vec, ll n){
    v64 pref(n);
    v64 maxpref(n);
    maxpref[n-1] = -INF;
    forn(i,0,n) pref[i] = vec[i] + (i == 0 ? 0 : pref[i-1]);

    for(ll i = n-2; i >= 0; i--){
        maxpref[i] = max(pref[i], (i == n-1 ? -INF : maxpref[i+1]));
    }

    ll fp = -1;

    debugv(pref);
    debugv(maxpref);
    forn(i,0,n-2){
        if(pref[i] >= 0){
            fp = i;
            break;
        }
    }

    forn(i,0,n-2){
        if(pref[i] >= 0 && maxpref[i+1] >= pref[i]) return {INF, 1};
    }

    return {fp,0};
}   

void solve(){
    ll n, k; cin >> n >> k;

    v64 vec(n);
    ll tot = 0;

    forn(i,0,n){
        ll x; cin >> x;
        if(x <= k) vec[i] = 1;
        else vec[i] = -1;
        tot += vec[i];
    }
    
    // procura por l r tal que 2 dos 3 vale sum(1..l) >= 0 sum(r+1..n) >= 0 sum(l+1,...,r) >=0
    
    p64 aux = func(vec, n);
    if(aux.second){
        cout << "YES" << ln;
        debug(1);
        return;
    }    
    ll fp = aux.first;
    reverse(vec.begin(), vec.end());
    
    aux = func(vec, n);
    
    if(aux.second){
        debug(2);
        cout << "YES" << ln;
        return;
    }
    
    ll fs = n-1 - aux.first;
    
    if(fp != -1 && fs != n && fp < fs){
        debug(fp); 
        debug(fs);
        debug(3);
        cout << "YES" << ln;
    }else{
        cout << "NO" << ln;
    }
}   

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
