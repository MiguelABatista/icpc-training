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
    ll n, x; cin >> n >> x; 
    ll mod = 1000000000+7;
    v64 coins(n);  
    v64 dp(x+1, 0);
    forn(i,0,n){
        cin >> coins[i];
    }
 
    forn(c,0,n){
        forn(i,0,x+1){
            ll cum_sum = dp[i]; 
            if(i == coins[c]){
                cum_sum++;
            }
            if(i - coins[c] > 0){
                cum_sum = (cum_sum + dp[i- coins[c]])%mod;
            } 
            dp[i] = cum_sum;
        }
    }
    cout << dp[x] << ln; 
    return 0;
}