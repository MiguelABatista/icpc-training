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
const ll MOD = 1'000'000'007;

int main() {
    _;
    ll n, m; cin >> n >> m;
    ll lim = 1<<n;
    v64 dp(lim, 0);
    v64 dp_next(lim, 0);
    dp[0] = 1;
    
    function<void (ll, ll, ll)> func = [&](ll mask, ll i, ll nmask){
        ll pot = (1<<i);
        if(i >= n){
            dp_next[nmask] = (dp_next[nmask]+dp[mask])%MOD;
            return;
        }
        if(mask&pot) return func(mask, i+1, nmask);
        func(mask, i+1, nmask+pot);
        if(i + 1 < n && (mask&(2*pot)) == 0) func(mask, i+2, nmask);
    };

    forn(i,0,m){
        forn(mask, 0, lim) func(mask, 0, 0);
        swap(dp, dp_next);
        dp_next.assign(lim, 0);
    }

    cout << dp[0] << ln;
    return 0;
}
