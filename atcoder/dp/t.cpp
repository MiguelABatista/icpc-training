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
    string s; cin >> s;
    vector<vll> dp(n, vll(n));
    vll pref(n);
    // dp[i][j] é a qtd de soluções pro pref i sendo o último cara o j menor (j <= i);
    dp[0][0] = 1;

    auto sum = [&](ll l, ll r){
        if(r < l) return 0ll;
        return (pref[r] - (l == 0 ? 0 : pref[l-1]) + MOD)%MOD;
    };

    debug(s);

    forn(i,1,n){
        forn(j,0,n) pref[j] = (dp[i-1][j] + (j == 0 ? 0ll : pref[j-1]))%MOD;
        forn(j,0,i+1){
            if(s[i-1] == '>'){
                dp[i][j] = sum(j,n-1);
            }else{
                dp[i][j] = sum(0,j-1);
            }
        }
    }
    ll ans = 0;
    forn(i,0,n) ans = (ans+dp[n-1][i])%MOD;
    cout << ans%MOD << ln;
    forn(i,0,n){debugv(dp[i]);}
    return 0;
}
