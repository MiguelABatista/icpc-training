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

ll MAXA = 4010;

int main(){
    _;
    ll n; cin >> n;
    v64 vec(n);
    vector<v64> dp(5, v64(2*MAXA, 0));

    forn(i,0,n) cin >> vec[i];

    forn(i,0,n){
        if(vec[i] >= 0){
            for(ll j = 2*MAXA-1; j >= 0; j--){
                if(j+vec[i] >= 2*MAXA) continue;
                dp[4][j+vec[i]] += dp[3][j];
                dp[3][j+vec[i]] += dp[2][j];
                dp[2][j+vec[i]] += dp[1][j];
            }
        }else{
            for(ll j = 0; j < 2*MAXA; j++){
                if(j+vec[i] < 0) continue;
                dp[4][j+vec[i]] += dp[3][j];
                dp[3][j+vec[i]] += dp[2][j];
                dp[2][j+vec[i]] += dp[1][j];
            }
        }
        
        dp[1][vec[i]+4000]++;    
    }

    ll q; cin >> q;

    forn(i,0,q){
        ll aux; cin >> aux;
        cout << dp[4][aux+4000] << ln;
    }
    return 0;
}