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

int main() {
    _;ll n, t; cin >> n >> t;
    vector<vector<pll>> events(t+1);
    vll dp(t+2);
    dp[t+1] = 0;

    forn(i, 0, n){
        ll happy, duration, tot; cin >> happy >> duration >> tot;
        forn(j,0, tot){
            ll start; cin >> start;
            events[start].push_back({min(start+duration, t+1), happy});
        }
    }

    for(ll i = t; i >= 0; i--){
        dp[i] = dp[i+1];
        for(auto [f, h] : events[i]){
            debug(h);
            debug(f);
            debug(dp[f]);
            debug(dp[i]);
            dp[i] = max(h + dp[f], dp[i]);
        }
    }

    cout << dp[0] << ln;

    return 0;
}
