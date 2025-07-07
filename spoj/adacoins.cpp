// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("avx,avx2,fma")

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
const ll MAXV = 100'000;


int main(){
    _;
    ll n, q; cin >> n >> q;

    bitset<100'001> bs;
    v64 dp(MAXV+1,0);

    bs[0] = 1;

    forn(i,0,n){
        ll curr; cin >> curr;
        bs |= bs << curr;
    }
    
    // forn(i,0,20) cout << dp[i] << " "; cout << ln;

    forn(i,1,MAXV+1){
        dp[i] += dp[i-1] + bs[i];
    }

    // forn(i,0,20) cout << dp[i] << " "; cout << ln;

    forn(i,0,q){
        ll b, e; cin >> b >> e;
        cout << dp[e] - dp[b-1] << ln;
    }
    return 0;
}