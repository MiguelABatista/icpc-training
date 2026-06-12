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
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    sort(vec.rbegin(), vec.rend());

    bool bom = true;
    debugv(vec);
    forn(i,0,n-2){
        if(vec[i+2] != vec[i]%vec[i+1]){
            debug(vec[i+2]);
            debug(vec[i+1]);
            debug(vec[i]);
            bom = false;
            break;
        }
    }
    if(bom){
        cout << vec[0] << " " << vec[1] << ln;
        return;
    }
    cout << -1 << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
