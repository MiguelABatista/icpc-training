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
const ll MAXSUM = 8010;

int main(){
    _;
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    // vector<v64> dp(5,v64(MAXSUM+100, 0));
    vector<map<ll,ll>> dp(5);

    forn(i,0,n){
        if(vec[i] < 0){
            forn(j,-MAXSUM/2,MAXSUM/2){
                // if(j+vec[i] < 0 || j+vec[i] > MAXSUM) continue;
                dp[2][j+vec[i]] += dp[1][j];
                dp[3][j+vec[i]] += dp[2][j];
                dp[4][j+vec[i]] += dp[3][j];
            }
        }  
        if(vec[i] >= 0){
            for(ll j = MAXSUM/2; j >= -MAXSUM/2; j--){
                // if(j+vec[i] < 0 || j+vec[i] > MAXSUM) continue;
                dp[2][j+vec[i]] += dp[1][j];
                dp[3][j+vec[i]] += dp[2][j];
                dp[4][j+vec[i]] += dp[3][j];
            }
        }
        dp[1][vec[i]]++;
    }

    // forn(i,1,5){
    //     forn(j,-MAXSUM/2,MAXSUM/2){
    //         cout << dp[i][j] << " \n"[j == 0];
    //     }
    //     cout << ln;
    //     cout << ln;
    // }
 
    ll q; cin >> q;
    forn(i,0,q){
        ll val; cin >> val;
        cout << dp[1][val] << ln;
        cout << dp[2][val] << ln;
        cout << dp[3][val] << ln;
        cout << dp[4][val] << ln;
    }
    return 0;
}