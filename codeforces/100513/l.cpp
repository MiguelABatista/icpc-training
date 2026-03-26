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

// Dominator Tree (Lengauer-Tarjan)
//
// builds the dominator tree given a directed graph and a source.
// returns a vector where ret[u] is the immediate dominator of u.
//
// complexity: O((N+M) log N), O(N+M) mem

v64 DomTree(vector<v64>& graph, ll src) {
    ll n = sz(graph);
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

void solve(ll n, ll m){    
    vector<p64> edges;
    vector<v64> g(n);
    forn(i,0,m){
        ll a, b; cin >> a >> b;
        a--, b--;
        edges.push_back({a,b});
        g[a].push_back(b);
    }   

    v64 dom = DomTree(g, 0);
    v64 in(n, -1), out(n);
    ll t = 0;
    vector<v64> tree(n);

    forn(i,0,n){
        if(dom[i] == -1) continue;
        tree[dom[i]].push_back(i);
    }

    function<void (ll)> dfs = [&](ll u) {
        in[u] = t++;
        for(ll v: tree[u]){
            if(in[v] == -1){
                dfs(v);
            }
        }
        out[u] = t++;
    };

    auto anc = [&](ll a, ll b) { // se a eh ancestral de b
        return in[a] <= in[b] and out[a] >= out[b];
    };

    dfs(0);

    v64 resp;
    forn(i,0, sz(edges)){
        auto [a,b] = edges[i];
        if(anc(b,a)) continue;
        if(in[a] == -1) continue;
        resp.push_back(i);
    }

    cout << sz(resp) << ln;
    forn(i,0,sz(resp)) cout << resp[i]+1 << " \n"[i==n-1];
}

int main() {
    _;
    ll n, m;
    while (cin >> n >> m) {
        solve(n,m);
    }
    return 0;
}
