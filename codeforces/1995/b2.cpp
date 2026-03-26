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

ll func(ll x, ll c, ll d, ll m){
    // find max(ax+b(x+1)) 
    // st
    // a <= c
    // b <= d
    // ax+b(x+1) <= m;
    
    ll curr = 0;
    ll a = min(c, m/x);
    c -= a;
    curr += a*x;
    ll gap = m - curr;
    ll b = min(d, gap/(x+1));
    curr += b*(x+1);
    gap = m - curr;
    d -= b; 

    ll tomove = min(min(a,d), gap);
    curr += tomove;
    return curr; 
}

void solve(){
    ll n, m; cin >> n >> m;
    vector<p64> vec(n);

    forn(i,0,n) cin >> vec[i].first;
    forn(i,0,n) cin >> vec[i].second;
    sort(vec.begin(), vec.end());

    ll best = 0;
    forn(i,0,n){
        ll aux = min(m/vec[i].first, vec[i].second);
        best = max(best, aux*vec[i].first);
        if(i == n-1 || vec[i].first+1 != vec[i+1].first) continue;
        best = max(best, func(vec[i].first, vec[i].second, vec[i+1].second, m));
    } 

    cout << best << ln;
    trace(cout << "------------------\n\n");
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
