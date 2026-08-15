#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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

ll ff(vll& a, vll& p, vll& r, ll d, ll n){
    ll v = 0;
    ll c = 0;
    ll m = sz(p);

    forn(i,0,sz(a)){
        if(a[i] == 1){
            v += d;
            c++;
        } 
        else{
            c = 0;
        }
        forn(j,0,m){
            if(c == p[j]) v += r[j];
        }
        if(c == n) c = 0;
    }
    return v;
}


void solve(){
    ll n, m, d; cin >> n >> m >> d;
    vll p(n);
    vll r(n);
    vll pref(n);
    forn(i,0,n) cin >> p[i];
    forn(i,0,n){
        cin >> r[i];
        pref[i] = r[i] + (i == 0 ? 0 : pref[i-1]);
    }

    auto f = [&](ll x){
        
    }
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
