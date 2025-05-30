#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _;
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    v64 dp(n,INF);

    dp[n-1] = 0;
    dp[n-2] = abs(vec[n-2]-vec[n-1]);

    for(ll i = n-3; i >= 0; i--){
        dp[i] = min(dp[i+1] + abs(vec[i] - vec[i+1]), dp[i+2] + abs(vec[i] - vec[i+2]));
    }

    cout << dp[0] << ln;
    return 0;
}