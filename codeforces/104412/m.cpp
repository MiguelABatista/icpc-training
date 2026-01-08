#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << _LINE_ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MOD = 998244353;

int main(){
    _; ll n; cin >> n;
    v64 v(n), dp(n), last_smaller(n), dps(n), sdps(n);
    forn(i, 0, n) cin >> v[i];

    last_smaller[0] = -1;

    forn(i, 1, n){
        ll last = i-1;
        while(last != -1 && v[last] > v[i]) last = last_smaller[last];
        last_smaller[i] = last;
    }

    dp[0] = 1;
    dps[0] = 1;
    sdps[0] = 1;

    debugv(last_smaller);

    forn(i, 1, n){
        if(last_smaller[i] == -1) dps[i] = (sdps[i-1] + 1)%MOD;
        else dps[i] = (MOD + sdps[i-1] - sdps[last_smaller[i]] + dp[last_smaller[i]])%MOD;
 
        dp[i] = dps[i];
        if(last_smaller[i] != -1) dp[i] = (dp[i] + dp[last_smaller[i]])%MOD;

        sdps[i] = (sdps[i-1] + dps[i])%MOD;
    }

    cout << dp[n-1] << ln;

    return 0;
}