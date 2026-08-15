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
const ll MAX = 20'005;


void solve(){
    ll x, y; cin >> x >> y;
    ll best = INF;
    ll bn = -1;
    ll bp = -1;
    forn(n,0,MAX){
        ll z = (n*(n+1))/2;
        ll p = min(z,(z+x-y)/2);
        p = max(p,0ll);
        ll q = z-p;
        if(p > x || q > y) continue;
        ll d = (x-p)*(x-p) + (y-q)*(y-q);
        if(d < best){
            best = d;
            bn = n;
            bp = p;
        }
    }
    debug(best);
    debug(bn);
    debug(bp);
    for(ll i = bn; i > 0; i--){
        if(i <= bp){
            cout << "X";
            bp -= i;
        }else{
            cout << "Y";
        }
    }
    cout << ln;
    trace(cout << "-----------------\n\n";)
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
