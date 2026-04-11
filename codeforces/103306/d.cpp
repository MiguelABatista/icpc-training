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
    ll c, r, s; cin >> c >> r >> s;
    ll tot = (c+r+s-1)/s;
    if(r == 0){
        cout << tot << " " << tot << ln;
        return;
    }
    cout << tot - (r+s-1)/s << " " << tot - min(tot, r) << ln;
}

int main() {
    _;ll t; cin >> t; 
    forn(i, 0, t) solve();
    return 0;
}
