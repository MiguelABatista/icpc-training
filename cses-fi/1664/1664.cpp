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
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << setw(3) <<  xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MAX = 1'000'005;
// const ll MAX = 15;
const ll LOG = 32;
// const ll LOG = 4;

int main() {
    _;
    ll n, q; cin >> n >> q;

    v64 fim(MAX, MAX-1);
    v64 dp(MAX, MAX-1);

    forn(i,0,n){
        ll a, b; cin >> a >> b;
        fim[a] = min(fim[a], b);
    }

    for(ll i = MAX-2; i >= 0; i--){
        dp[i] = min(fim[i], dp[i+1]);
    }

    vector<v64> bl(LOG, v64(MAX, MAX-1));

    forn(i,0,MAX) bl[0][i] = dp[i];

    forn(j,1,LOG){
        forn(i,0,MAX){    
            // trace(
            //     cout << i << " " << j << " " << bl[j-1][i] << " " << bl[j-1][bl[j-1][i]] << ln;
            // )
            bl[j][i] = bl[j-1][bl[j-1][i]];
        }
    }

    // trace(
    //     cout << "-------";
    //     forn(i,0,MAX) cout << setw(3) << i << " ";; cout << ln; 
    //     forn(i,0,4){debugv(bl[i]);};
    // );

    while(q--){
        ll a, b; cin >> a >> b;
        ll p = a;
        ll resp = 0;
        debug(b);
        debug(p);
        for(ll j = LOG-1; j >= 0; j--){
            if(bl[j][p] <= b){
                p = bl[j][p];
                resp += (1ll<<j);
            } 
        }
        cout << resp << ln;
    }
    return 0;
}
