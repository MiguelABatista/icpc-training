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

int main() {
    _;
    ll n; cin >> n;
    vector<vll> dp(n, vll(n));
    vector<string> tab(n);
    forn(i,0,n) cin >> tab[i];
    dp[n-1][n-1] = (tab[n-1][n-1]=='.') ;

    for(ll i = n-1; i >= 0; i--){
        for(ll j = n-1; j >= 0; j--){
            if(tab[i][j] == '*') continue;
            dp[i][j] = (dp[i][j] + (i+1 < n ? dp[i+1][j] : 0))%MOD;
            dp[i][j] = (dp[i][j] + (j+1 < n ? dp[i][j+1] : 0))%MOD;
        }
    }

    cout << dp[0][0] << ln;
    return 0;
}
    