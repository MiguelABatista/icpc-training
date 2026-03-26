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
    vector<p64> ed;
    forn(i,0,m){
        ll a, b; cin >> a >> b;
        a--, b--;
        ed.push_back({a,b});
        g[a].push_back(b);
    }

    v64 vis(n, 0);
    v64 par(n, -1);
    v64 in(n,0);
    v64 out(n,0);
    v64 prof(n, 0);
    ll t = 0;
    function<void (ll, ll)> dfs = [&](ll u, ll p){
        vis[u] = 1;
        par[u] = p;
        in[u] = t++;
        if(p != -1) prof[u] = prof[p] + 1;

        for(ll v: g[u]){
            if(vis[v]) continue;
            debug(u);
            debug(v);
            dfs(v,u);
        }
        out[u] = t++;
    };

    forn(i,0,n){
        if(!vis[i]) dfs(i, -1);

    }

    auto anc = [&](ll a, ll b){ // se a eh ancestral de b
        return in[a] <= in[b] && out[a] >= out[b];
    };
    
    debugv(par);
    for(auto [a,b] : ed){
        if(!vis[a] || !vis[b]) continue;
        if(!anc(b,a)) continue;
        v64 cic;
        ll x = a;
        debug(a);
        debug(b);
        do{
            cic.push_back(x);            
            debug(x);
            x = par[x];
        }while(x != b);
        cic.push_back(x);
        cic.push_back(a);
        reverse(cic.begin(), cic.end());
        cout << sz(cic) << ln;
        for(ll y: cic) cout << y+1 << " ";; cout << ln;
        return 0;
    }
    cout << "IMPOSSIBLE" << ln;
    return 0;
}
