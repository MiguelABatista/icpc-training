#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
const ll MAX = 10;
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
const ll MAX = 50'005;
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Strongly Connected Components (Kosaraju)
//
// Computes SCCs using two DFS passes and builds the condensation graph.
//
// complexity: O(N + M), O(N + M)

vector<bool> visited;

void dfs(ll v, vector<vll>& g, vll &out) {
    visited[v] = true;
    for(auto u : g[v]) if(!visited[u]) dfs(u, g, out);
    out.push_back(v);
}

pair<vector<vll>, vll> scc(vector<vll>& g) {
    int n = sz(g);
    vll order, roots(n, 0);

    vector<vll> adj_rev(n);
    forn(u, 0, n) for (ll v : g[u]) adj_rev[v].push_back(u);

    visited.assign(n, false);
    forn(i, 0, n) if (!visited[i]) dfs(i, g, order);
    reverse(order.begin(), order.end());
    
    visited.assign(n, false);
    ll curr_comp = 0;
    for (auto v : order) {
        if (!visited[v]) {
            vll component; dfs(v, adj_rev, component);
            for (auto u : component) roots[u] = curr_comp;
            curr_comp++;
        }
    }

    set<pll> edges;
    vector<vll> cond_g(curr_comp);
    forn(u, 0, n) {
        for (auto v : g[u]) {
            if (roots[u] != roots[v] && !edges.count({roots[u], roots[v]})) {
                cond_g[roots[u]].push_back(roots[v]);
                edges.emplace(roots[u], roots[v]);
            }
        }
    }
    return {cond_g, roots};          
}


int main() {
    _;
    ll nn, m, q; cin >> nn >> m >> q;
    vector<vll> g2(nn);
    forn(i,0,m){
        ll a, b; 
        cin >> a >> b;
        a--, b--;
        g2[a].push_back(b);
    }
    auto [g, r] = scc(g2);
    ll n = sz(g);
    vector<bitset<MAX>> mem(n);
    vll vis(n);
    vll resp(n);

    function<void (ll)> dfs = [&](ll u){
        vis[u] = 1;
        mem[u][u] = 1;
        for(ll v: g[u]){
            if(!vis[v]) dfs(v);
            mem[u] |= mem[v];
        }
        resp[u] = mem[u].count();
    };

    forn(i,0,n) if(!vis[i]) dfs(i);

    while(q--){
        ll a, b; cin >> a >> b;
        a--, b--;
        if(mem[r[a]][r[b]]) cout << "YES\n";
        else cout << "NO\n";
    }    

    return 0;
}
