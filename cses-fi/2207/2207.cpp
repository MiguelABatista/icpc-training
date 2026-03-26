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
const ll MAX = 2000;

v64 gru(MAX);
void prep(){
    gru[1] = 0;
    gru[2] = 0;

    forn(i,3,MAX){
        set<ll> s;
        forn(j,1,(i+1)/2){ 
            if(j == i-j) continue;
            s.insert(gru[j]^gru[i-j]);
        }

        ll mex = 0;
        while (s.count(mex)) mex++;
        gru[i] = mex;        
    }
}

void solve(){
    ll n; cin >> n;
    if(n >= MAX){
        cout << "first" << ln;
        return;
    }
    if(gru[n]) cout << "first" << ln;
    else cout << "second" << ln;
}

int main() {
    _;
    prep();
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
