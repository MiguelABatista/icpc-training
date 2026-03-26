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

v64 scc(vector<v64>& g) {
    int n = sz(g);
    v64 order, roots(n, 0);

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
    return roots;
}


int main() {
    _;
    ll n, m;
    cin >> n >> m;
    vector<v64> g(n);
    forn(i,0,m){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }

    auto comp = scc(g);
    ll k = 0;
    forn(i,0,n) k = max(k, comp[i]);
    if(k == 0){
        cout << "YES" << ln;
        return 0;
    }
    cout << "NO" << ln;
    ll a = 0;
    ll b = 0;
    forn(i,0,n){
        if(comp[i] == 0) a = i;
        if(comp[i] == 1) b = i;
    }    
    cout << b + 1 << " " << a+1 << ln;
    return 0;
}
