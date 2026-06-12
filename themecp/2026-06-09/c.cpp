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
    ll r; cin >> r;
    ll resp = 0;
    ll x = r;
    ll y = 0;
    debug(r);
    while(x > 0){
        y++;
        debug(y);
        while(x > 0 && (x-1)*(x-1)+y*y >= r*r){
            if(x*x+y*y < (r+1)*(r+1) && x*x+y*y >= r*r){
                trace(cout << x << ":" << y << ln;)
                resp++;
            }
            x--;
        }
        if(x*x+y*y < (r+1)*(r+1) && x*x+y*y >= r*r){
            trace(cout << x << ":" << y << ln;)
            resp++;
        }
        debug(resp);
    }

    cout << 4*resp << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
