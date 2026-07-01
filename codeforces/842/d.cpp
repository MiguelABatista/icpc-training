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
const ll MAX = 1048576;

void solve(){
    ll n, m; cin >> n >> m;
    vll vec(n);
    vll tem(MAX);
    vll acc(MAX);
    forn(i,0,n){
        ll x; cin >> x;
        tem[x] = 1;
    }  
    forn(i,0,n) acc[i] = (i == 0 ? 0 : acc[i-1]) + tem[i];
    
    auto sum = [&](ll l, ll r){
        return acc[r] - (l == 0 ? 0 : acc[l-1]);
    };

    while(m--){
        ll x; cin >> x;
        ll l = 0;
        ll r = (1<<19);
        for(ll i = 19; i >= 0; i--){

        }
    }
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
