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


vector<v64> g;
v64 dp;
v64 subsize;
v64 resp;
ll n;

void dfs(ll u, ll p){
    ll curr_sum = 0;
    ll curr_size = 0;

    for(ll v: g[u]){
        if(v == p) continue;

        dfs(v,u);

        curr_sum +=  dp[v] + subsize[v];
        curr_size += subsize[v];
    }

    dp[u] = curr_sum;
    subsize[u] = curr_size + 1;
}

void dfs2(ll u, ll p){
    if(p != -1){
        resp[u] = resp[p] + n - 2*subsize[u];
    }

    for(ll v: g[u]){
        if(v == p) continue;
        dfs2(v,u);
    }
}

int main(){
    _;
    cin >> n;
    g.resize(n);
    dp.resize(n, -1);
    subsize.resize(n, 1);
    resp.resize(n, 0);

    forn(i,0,n-1){
        ll a,b; cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0,-1);
    resp[0] = dp[0];

    dfs2(0,-1);

    forn(i,0,n) cout << resp[i] << " \n"[i==n-1];
    
    return 0;
}