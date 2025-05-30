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

v64 dp;
vector<v64> g;

ll dfs(ll v){
    if(dp[v] != -1) return dp[v];

    ll resp = 0;

    for(ll u: g[v]){
        resp = max(dfs(u)+1, resp);
    }

    dp[v] = resp;
    debug(v);
    debug(dp[v]);
    return resp;
}

int main(){
    _;
    ll n, m;
    cin >> n >> m;
    g.resize(n);
    
    dp.resize(n,-1);

    forn(i,0,m){
        ll x, y; cin >> x >> y;
        x--; y--;
        g[x].push_back(y);
    }

    forn(i,0,n){
        if(dp[i] != -1) continue;
        dfs(i);
    }

    ll resp = -1;
    forn(i,0,n) resp = max(resp, dp[i]);

    cout << resp << ln;
    
    return 0;

}