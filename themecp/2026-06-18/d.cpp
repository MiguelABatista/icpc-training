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

void solve(){
    ll n, m, k; cin >> n >> m >> k;
    vll a(n), d(m), f(k);
    forn(i,0,n){
        cin >> a[i];
        a[i] *= 2;
    }
    forn(i,0,m) {
        cin >> d[i];
        d[i] *= 2;
    }
    forn(i,0,k){
        cin >> f[i];
        f[i] *= 2;
    }
    sort(f.begin(), f.end());

    vector<pll> diff(n-1);
    forn(i,0,n-1) diff[i] = {a[i+1]-a[i], i};
    sort(diff.rbegin(), diff.rend());

    ll val = -INF;
    if(n > 2){
        ll vv1 = diff[0].first;
        val = diff[1].first;
        if(vv1 == val){
            cout << val/2 << ln;
            return;
        }
    }
    ll resp = diff[0].first;

    ll x = a[diff[0].second];
    ll y = a[diff[0].second+1];
    ll z = (x+y)/2;
    ll cte = z-x;

    forn(i,0,m){
        ll t = z-d[i];
        auto it = lower_bound(f.begin(), f.end(), t);
        ll v1 = INF;
        ll v2 = -INF;
        if(it != f.end()) v1 = *it;
        if(it != f.begin()) v2 = *prev(it);
        ll tenta1 = max(val, cte + z-(d[i]+v2));
        ll tenta2 = max(val, cte + (d[i]+v1)-z);
        resp = min({resp, tenta1, tenta2});
    }
    cout << resp/2 << ln;
}   

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
