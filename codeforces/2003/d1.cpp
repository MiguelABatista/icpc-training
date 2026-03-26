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

    forn(i,0,n){
        ll l; cin >> l;
        forn(j,0,l){
            ll x; cin >> x;
            vec[i].push_back(x);
        }
    }
    

    forn(i,0,n) sort(vec[i].begin(), vec[i].end());

    vector<p64> mexts(n);
    forn(i,0,n) mexts[i] = mext(vec[i]);

    ll best = 0;
    forn(i,0,n) best = max(best, mexts[i].second);

    ll resp = 0;
    if(m <= best){
        resp = (m+1)*best;
    }else{
        resp = (best+1)*best;
        // best+1 + best+2 + ... + m
        // = m(m+1)/2 - best(best+1)/2;
        resp += m*(m+1)/2 - best*(best+1)/2;
    }
    cout << resp << ln;

    trace(cout << "------------------\n\n");
}
int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();

    return 0;
}
