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
    #define debugp(x) cout << __LINE__ << ": " << #x << " = " << x.first << " " << x.second << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
    #define debugp(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MULT = 2;

void solve(){
    ll n, m; cin >> n >> m;
    vector<v64> g(n);
    ll t = MULT*n;

    forn(i,0,m){
            ll a, b;
            cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }     

    vector<vector<p64>> dp(2,vector<p64>(MULT*n+2,{INF,INF}));

    dp[(t+1)&1][n-1] = {MULT*n+1, 0};

    // forn(i,0,n) cout << i+1 << ": " << dp[i][t+1].first << " " << dp[i][t+1].second << ln; 

    for(;t >= 0; t--){
        forn(u,0,n-1){
            ll prox = g[u][t%((ll)g[u].size())];
            if(u != n-1){
                if(dp[(t+1)&1][prox] <= dp[(t+1)&1][u]){
                    dp[(t)&1][u] = dp[(t+1)&1][prox]; 
                }else{
                    dp[(t)&1][u] = {dp[(t+1)&1][u].first, dp[(t+1)&1][u].second+1}; 
                }
                
            }
        };
        // debug(t);
        // forn(i,0,n) cout << i+1 << ": " << dp_curr[i].first << " " << dp_curr[i].second << ln; 
        // cout << ln;
        dp[(t)&1][n-1] = {t,0};

    }
    cout << dp[0][0].first << " " << dp[0][0].second << ln;
}

int main(){
    _;
    ll t; cin >> t; 
    while(t--) solve();
    return 0;
}