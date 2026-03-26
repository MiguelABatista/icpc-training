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

p64 mext(v64& vec){
    ll n = sz(vec);
    ll mex = 0;
    ll idx = 0;
    while(idx < n && vec[idx] <= mex){
        if(vec[idx] == mex) mex++;
        idx++;
    }
    p64 resp = {-1, -1};
    resp.first = mex;
    mex++;
    while(idx < n && vec[idx] <= mex){
        if(vec[idx] == mex) mex++;
        idx++;
    }
    resp.second = mex;
    return resp;
}

void solve(){
    ll n, m; cin >> n >> m;
    vector<v64> vec(n);
    vector<set<ll>> vset(n);

    ll maxl = 0;
    forn(i,0,n){
        ll l; cin >> l;
        maxl = max(maxl, l);
        forn(j,0,l){
            ll x; cin >> x;
            vec[i].push_back(x);
            vset[i].insert(x);
        }
    }
    
    maxl += 5;

    forn(i,0,n) sort(vec[i].begin(), vec[i].end());

    vector<p64> mexts(n);
    forn(i,0,n) mexts[i] = mext(vec[i]);
    forn(i,0,n) cout << mexts[i].first << " " << mexts[i].second << ln;

    v64 one_op(maxl, 0);
    forn(i,0,maxl) one_op[i] = i;

    forn(i,0,n){
        for(ll x: vec[i]){
            one_op[x] = max(one_op[x], mexts[i].first);
        }
    }

    forn(i,0,n) one_op[mexts[i].first] = max(one_op[mexts[i].first], mexts[i].second);

    v64 more_op(maxl,0);
    
    for(ll i = maxl-1; i >= 0; i--){
        more_op[i] = max(i, more_op[one_op[i]])
    }

    trace(cout << "------------------\n\n");
}
int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();

    return 0;
}
