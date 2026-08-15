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
const ll MOD = 1'000'000'007;
const ll MAX = 61;

void solve(){
    ll n; cin >> n;

    vector<vector<vector<vll>>> dp(MAX, vector<vector<vll>>(2, vector<vll>(2, vll(2, -1))));
    // how many a < c st a^c = 2*(a&c);
    // prefix i, is c < n, is a < c, needed bit (define by the xor);

    function<ll (ll, ll, ll, ll)> rec = [&](ll i, ll cless, ll aless, ll bitandd){
        if(i < 0) return (ll)(!bitandd && aless);
        if(dp[i][cless][aless][bitandd] != -1) return dp[i][cless][aless][bitandd];
        
        ll pot = 1ll<<i;
        ll bitn = ((n&pot)!=0);
        ll resp = 0;

        if(bitandd){
            ll bita = 1;
            ll bitc = 1;
            if(!cless && !bitn) return dp[i][cless][aless][bitandd] = 0;
            return dp[i][cless][aless][bitandd] = rec(i-1, cless, aless, bita^bitc);
        }

        // need = 0
        ll ans = 0;
        forn(bita,0,2) forn(bitc,0,2) if((bita&bitc) == 0){
            ll ncless = cless || (bitc < bitn);
            ll naless = aless || (bita < bitc);
            if(!cless && bitc > bitn) continue;
            if(!aless && bita > bitc) continue;
            ans += rec(i-1, ncless, naless, bita^bitc);
        }
        return dp[i][cless][aless][bitandd] = ans%MOD;
    };

    cout << rec(60,0,0,0) << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
