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
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _;
    ll n, m; cin >> n >> m;
    v64 vec(n);
    
    if(n == 1){
        cout << 0 << ln;
        return 0;
    }
    
    forn(i,0,n) cin >> vec[i];

    vector<vector<ll>> dp(n, v64(m));

    forn(i,0,m-1) dp[1][i] = -100;
    forn(i,2,n){
        forn(j,0,m-1){
            dp[i][j] = dp[i-1][j+1];
        }
        dp[i][m-1] = dp[i-1][0] + vec[i-1];
        dp[i][0] = max(dp[i][0], dp[i-1][0]);
    }   

    ll resp = dp[n-1][0] + vec[n-1];

    forn(i,1,m) resp = max(resp, dp[n-1][i]);

    trace(
        forn(i,0,n) cout << vec[i] << " ";; cout << ln;
        forn(j,0,m){
            forn(i,0,n){
                cout << dp[i][j] << " ";
            }
            cout << ln;
        }
    );

    cout << resp << ln;
    return 0;
}