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
    ll n, x; cin >> n >> x;

    vll coins(n);
    forn(i,0,n) cin >> coins[i];

    vll dp(x+1);
    // dp[i] = quantas maneiras eu tenho de somar i 
    // usando as moedas
    dp[0] = 1;
    
    forn(i,1,x+1){
        ll acc = 0;
        forn(j,0,n){
            if(i - coins[j] < 0) continue;
            acc = (acc + dp[i-coins[j]])%MOD;
        }
        dp[i] = acc;
    }

    cout << dp[x] << ln;
    return 0;
}
