#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
 
int main() {
    _;
    ll n, m; cin >> n >> m;
    vector<v64> g(n);
    forn(i,0,m){
        ll a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
    }
 
    v64 vis(n);
    v64 maxf(n, -INF);
    v64 par(n);

    function<void (ll)> dfs = [&](ll u){
        vis[u] = 1;
        ll maf = -INF;
        ll p = -1;
        if(u == n-1) maf = 0;

        for(ll v: g[u]){
            if(!vis[v]) dfs(v);
            if(maxf[v] > maf){
                p = v;
                maf = maxf[v];
            }
        }
        if (u == n - 1) {
            maxf[u] = 0;
            par[u] = -1;
        } else {
            maxf[u] = maf + 1;
            par[u] = p;
        }
        return;
    };
    dfs(0);
    if(maxf[0] < -(INF/2)){
        cout << "IMPOSSIBLE" << ln;
        return 0;
    }
    cout << maxf[0]+1 << ln;
    ll x= 0;
    forn(i,0,maxf[0]+1){
        cout << x+1 << " ";
        x = par[x];
    }
    return 0;
}
