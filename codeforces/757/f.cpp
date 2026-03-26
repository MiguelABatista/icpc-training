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
#define debugp(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;


// Dominator Tree (Lengauer-Tarjan)
//
// builds the dominator tree given a directed graph and a source.
// returns a vector where ret[u] is the immediate dominator of u.
//
// complexity: O((N+M) log N), O(N+M) mem

v64 DomTree(vector<v64>& graph, ll src) {
    ll n = graph.size();
    vector<v64> tree(n), trans(n), buck(n);
    v64 semi(n), par(n), dom(n), label(n), atob(n, -1), btoa(n, -1),
        link(n, -1);

    function<ll(ll, ll)> find=[&](ll u, ll d){
        if(link[u] == -1) return d ? -1 : u;
        ll v = find(link[u], d + 1);
        if(v < 0) return u;
        if(semi[label[link[u]]] < semi[label[u]]) label[u] = label[link[u]];
        link[u] = v;
        return d ? v : label[u];
    };
    ll t = 0;
    function<void(ll)> dfs=[&](ll u){
        atob[u] = t;
        btoa[t] = u;
        label[t] = semi[t] = t;
        t++;
        for(auto v : graph[u]){
        if(atob[v] == -1) dfs(v), par[atob[v]] = atob[u];
        trans[atob[v]].push_back(atob[u]);
        }
    };
    dfs(src);
    for(ll u = t - 1; u >= 0; --u){
        for(auto v : trans[u]) semi[u] = min(semi[u], semi[find(v, 0)]);
        if(u) buck[semi[u]].push_back(u);
        for(auto w : buck[u]){
            ll v = find(w, 0);
            dom[w] = semi[v] == semi[w] ? semi[w] : v;
        }
        if(u) link[u] = par[u];
    }
    v64 ret(n, -1);
    forn(u,1,t) {
        if(dom[u] != semi[u]) dom[u] = dom[dom[u]];
        ret[btoa[u]] = btoa[dom[u]];
    }
    return ret;
}

// Dijkstra's Shortest Paths
//
// Computes single-source shortest paths on non-negative weighted graphs using a priority queue.
//
// complexity: O((N + M) log N), O(N + M)

vector<vector<p64>> g;

// d = distance | p = from/path
void dijkstra(ll s, v64 &d, v64& p) {
    ll n = g.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;
    priority_queue<p64> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        ll u = pq.top().second;
        ll d_u = -pq.top().first;
        pq.pop();

        if (d_u != d[u]) continue;

        for (auto edge : g[u]) {
            ll v = edge.first;
            ll w_v = edge.second;

            if (d[u] + w_v < d[v]) {
                d[v] = d[u] + w_v;
                p[v] = u;
                pq.push({-d[v], v});
            }
        }
    }
}

int main() {
    _;
    ll n, m, s; cin >> n >> m >> s;
    s--;
    g.resize(n);
    vector<pair<p64, ll>> edges;
    forn(i,0,m){
        ll a, b, w;
        cin >> a >> b >> w;
        a--, b--;
        edges.push_back({{a,b}, w});
        edges.push_back({{b,a}, w}); 
        g[a].push_back({b,w});
        g[b].push_back({a,w});
    }

    v64 d, pa;
    dijkstra(s,d,pa); 
    debugv(d);
    vector<p64> valid_edges;
    for(auto [p, w] : edges){
        auto [a,b] = p;
        if(d[a] + w != d[b]) continue;
        valid_edges.push_back({a,b});
    }

    vector<v64> ng(n);

    for(auto [a,b] : valid_edges) ng[a].push_back(b);
    debugp(valid_edges);
    v64 dom = DomTree(ng, s);
    v64 sub(n);

    vector<v64> tree(n);

    forn(i,0,n){
        if(dom[i] == -1) continue;

        tree[dom[i]].push_back(i);
    }

    function<void (ll)> dfs = [&](ll u){
        ll resp = 1;
        for(ll v: tree[u]){
            dfs(v);
            resp += sub[v];
        }
        sub[u] = resp;
    };

    dfs(s);

    ll best = 0;
    forn(i,0,n){
        if(i == s) continue;
        best = max(best, sub[i]);
    }

    cout << best << ln;
    return 0;
}
