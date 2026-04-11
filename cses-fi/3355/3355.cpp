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
#define sq(u) (u*u)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;


void solve(ll n){
    vector<p64> vec(n+1, {-1, -1});

    for(ll i = 0; i*i <= n; i++){        
        for(ll j = i; j*j <= n; j++){
            if(i*i+j*j > n) break;
            vec[i*i+j*j] = {i,j};
        }
    }

    forn(i,0,n+1){
        if(vec[i].first == -1) continue;
        ll t = n-i;
        if(vec[t].first == -1) continue;
        cout << vec[i].first << " " << vec[i].second << " " << vec[t].first << " " << vec[t].second << ln;
        
        // ll sum = sq(vec[i].first) + sq(vec[i].second) + sq(vec[t].first) + sq(vec[t].second);
        // if(sum != n){
            // cout << n << ln;
        // }
        
        return;
    }
}
int main() {
    _;
    ll t; cin >> t;
    while(t--){
        ll n; cin >> n;
        solve(n);
    }

    // forn(i,0,1001) solve(i);
    return 0;
}
