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
const ll MOD = 1020;
const ll TAM = 10000;


int main(){
    _;
    vector<vector<double>> dp(2, vector<double>(MOD,0));
    dp[0][0] = 1;

    forn(i,1,1000){
        forn(j,0,MOD){
            dp[i&1][j] = dp[(i-1)&1][j];
            dp[i&1][j] += dp[(i-1)&1][((j-(i*i))%MOD + MOD)%MOD];
            dp[i&1][j] /= 2;
        }
    }

    forn(j,0,MOD){
        cout << fixed << setprecision(2) << (dp[(TAM-1)&1][j] - 1.0/MOD) << " ";
    } cout << ln;
    return 0;
}