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
v64 curr;

ll ask(){
    cout << "? " << sz(curr) << " ";
    for(ll j: curr) cout << j+1 << " ";
    cout << endl;
    ll x; cin >> x;
    return x;
}

void solve(){
    curr.clear();
    ll n; cin >> n;
    v64 target(2*n);
    curr.push_back(0);
    ll idx = 1;

    while(sz(curr) < n){
        curr.push_back(idx);
        ll x = ask();

        if(x != 0){
            curr.pop_back();
            target[idx] = x;
        }
        idx++;
    }

    v64 incurr(2*n);
    for(ll x: curr) incurr[x] = 1;

    forn(i,0,2*n){
        if(incurr[i]) continue;
        if(target[i] != 0) continue;
        curr.push_back(i);
        ll x = ask();
        target[i] = x;
        curr.pop_back();
    }

    curr.clear();
    forn(i,0,2*n){
        if(incurr[i]) continue;
        curr.push_back(i);
    }
    
    forn(i,0,2*n){
        if(!incurr[i]) continue;
        curr.push_back(i);
        ll x = ask();
        target[i] = x;
        curr.pop_back();
    }

    cout << "! ";
    forn(i,0,2*n) cout << target[i] << " \n"[i==2*n-1];
    cout.flush();
}

int main() {
    _;
    curr.reserve(1000);
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
