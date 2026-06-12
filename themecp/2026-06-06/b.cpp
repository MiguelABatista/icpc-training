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
    ll n, q; cin >> n >> q;
    vll vec(n), uns(n), zer(n), jun(n), acc(n);

    forn(i,0,n){
        cin >> vec[i];
        uns[i] = (vec[i] == 1) + (i == 0 ? 0 : uns[i-1]);
        zer[i] = (vec[i] == 0) + (i == 0 ? 0 : zer[i-1]);
    }

    forn(i,0,n-1) if(vec[i] == vec[i+1]) jun[i] = 1;
    forn(i,0,n) acc[i] = jun[i] + (i == 0 ? 0 : acc[i-1]);  
    
    while(q--){
        ll l,r; cin >> l >> r;
        l--,r--;
        ll x = uns[r] - (l == 0 ? 0 : uns[l-1]);
        ll y = zer[r] - (l == 0 ? 0 : zer[l-1]);
        if(x%3 != 0 || y%3 != 0){
            cout << -1 << ln;
            continue;
        }
        ll z = acc[r-1] - (l == 0 ? 0 : acc[l-1]);
        cout << (r-l+1)/3 + (z== 0) << ln;
    }
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
