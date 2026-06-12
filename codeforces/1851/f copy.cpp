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

pair<pll,pll> func(vector<pll> vec, ll k){
    if(vec.empty()){
        return {{-1,-1},{-1,-1}};
    }
    if(sz(vec) == 1){
        
    }
    if(k == -1){
        debug(sz(vec));
        return (pair<pll,pll>){vec[0], vec[1]};
    }

    ll n = sz(vec);
    ll pot = (1ll << k);
    vector<pll> v0;
    vector<pll> v1;
    forn(i,0,n){
        if((vec[i].first&pot) == 0) v0.push_back(vec[i]);
        else v1.push_back(vec[i]);
    }
    auto [p00, p01] = func(v0, k-1);
    auto [p10, p11] = func(v1, k-1);

    ll r0 = (1ll<<31) - 1 - (p00.first^p01.first);
    ll r1 = (1ll<<31) - 1 - (p10.first^p11.first);
    if(r0 > r1) return {p00,p01};
    return {p10, p11};
}


void solve(){
    ll n, k; cin >> n >> k;
    k--;
    vector<pll> vec(n);
    forn(i,0,n){
        cin >> vec[i].first;
        vec[i].second = i;
    }

    auto [p0, p1] = func(vec, k);
    ll ansi = p0.second;
    ll ansj = p1.second;
    ll x = (1<<(k+1))-1 - (p0.first^p1.first);
    cout << ansi << " " << ansj << " " << x << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
