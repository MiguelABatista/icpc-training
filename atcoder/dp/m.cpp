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
    ll n, k; cin >> n >> k;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];

    vll dp(k+1);
    dp[k] = 1;
    vll pref(k+1);

    auto sum = [&](ll l, ll r){
        if(r > k) r = k;
        return (pref[r] + MOD - (l == 0 ? 0 : pref[l-1]))%MOD;
    };

    forn(i,0,n){
        pref[0] = dp[0];
        forn(j,1,k+1) pref[j] = (dp[j] + pref[j-1])%MOD;
        forn(j,0,k+1) dp[j] = sum(j,j+vec[i]);
    }

    cout << dp[0] << ln;
    
    return 0;
}
