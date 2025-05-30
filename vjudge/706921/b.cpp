#include <bits/stdc++.h>
using namespace std;

typedef int ll;
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
    // NOTE QUE EU TROQUEI O LL PRA INT PQ TAVA DANDO ERRO
    ll n, x; cin >> n >> x; 
    v64 prices(n+1, 0);
    v64 n_pages(n+1, 0);  
    vector<v64> dp(n+1, v64(x+1,0));
    
    forn(i,1,n+1){
        cin >> prices[i];
    }
    forn(i,1,n+1){
        cin >> n_pages[i];
    }
    
    forn(b,1,n+1){
        forn(i,0,x+1){
            ll cum_sum = 0; 
            if(i - prices[b] >= 0){
                cum_sum += dp[b-1][i- prices[b]] + n_pages[b];
            } 
            dp[b][i] = max(cum_sum, dp[b-1][i]);
        }
    }
    cout << dp[n][x] << ln; 
    return 0;
}