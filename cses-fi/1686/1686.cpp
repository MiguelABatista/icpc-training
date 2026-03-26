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

// Strongly Connected Components (Kosaraju)
//
// Computes SCCs using two DFS passes and builds the condensation graph.
//
// complexity: O(N + M), O(N + M)

vector<bool> visited;

void dfs(ll v, vector<v64>& g, vector<ll> &out) {
    visited[v] = true;
    for(auto u : g[v]) if(!visited[u]) dfs(u, g, out);
    out.push_back(v);
}

v64 roots;

vector<v64> scc(vector<v64>& g) {
    int n = sz(g);
    v64 order;
    roots.resize(n, 0);
    vector<v64> adj_rev(n);
    forn(u, 0, n) for (ll v : g[u]) adj_rev[v].push_back(u);

    visited.assign(n, false);
    forn(i, 0, n) if (!visited[i]) dfs(i, g, order);
    reverse(order.begin(), order.end());
    
    visited.assign(n, false);
    ll curr_comp = 0;
    for (auto v : order) {
        if (!visited[v]) {
            v64 component; dfs(v, adj_rev, component);
            for (auto u : component) roots[u] = curr_comp;
            curr_comp++;
        }
    }

    set<p64> edges;
    vector<v64> cond_g(curr_comp);
    forn(u, 0, n) {
        for (auto v : g[u]) {
            if (roots[u] != roots[v] && !edges.count({roots[u], roots[v]})) {
                cond_g[roots[u]].push_back(roots[v]);
                edges.emplace(roots[u], roots[v]);
            }
        }
    }
    return cond_g;          
}


int main() {
    _;
    ll n2, m; cin >> n2 >> m;
    vector<v64> g2(n2);
    v64 coins2(n2);
    
    forn(i,0,n2){
        cin >> coins2[i];
    }
    forn(i,0,m){
        ll a, b; 
        cin >> a >> b;
        a--, b--;
        g2[a].push_back(b);
    }
    auto g = scc(g2);
    ll n = sz(g);
    v64 coins(n);

    forn(i,0,n2){
        coins[roots[i]] += coins2[i];
    }

    debugv(roots);
    debugv(coins);
    forn(i,0,n){debugv(g[i]);};
    
    v64 dp(n);
    for(ll i = n-1; i >=0; i--){
        ll resp = 0;
        for(ll v: g[i]){
            resp = max(resp, dp[v]);
        }
        resp += coins[i];
        dp[i] = resp;
    }
    cout << *max_element(dp.begin(), dp.end()) << ln;
    return 0;
}
