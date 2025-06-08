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
ll resp = -1;

void dfs(ll u, ll p){
    ll first = -1;
    ll second = -1;
    for(ll v : g[u]){
        if(v == p) continue;
        dfs(v,u);
        if(dp[v] > first){  
            second = first;
            first = dp[v];
        }else if(dp[v] > second){
            second = dp[v];
        }
    }

    resp = max(resp, first + second + 1);
    dp[u] = first + 1;
}

int main(){
    ll n; cin >> n;
    g.resize(n);
    dp.resize(n,-1);

    forn(i,1,n){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0, -1);

    cout << resp + 1 << ln;
    return 0;

}