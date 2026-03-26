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


v64 DomTree(vector<v64>& graph, ll src) {
    ll n = graph.size();
    vector<v64> tree(n), trans(n), buck(n);
    v64 semi(n), par(n), dom(n), label(n), atob(n, -1), btoa(n, -1),
        link(n, -1);

    function<ll(ll, ll)> find = [&](ll u, ll d) {
        if (link[u] == -1) return d ? -1 : u;
        ll v = find(link[u], d + 1);
        if (v < 0) return u;
        if (semi[label[link[u]]] < semi[label[u]]) label[u] = label[link[u]];
        link[u] = v;
        return d ? v : label[u];
    };
    ll t = 0;
    function<void(ll)> dfs = [&](ll u) {
        atob[u] = t;
        btoa[t] = u;
        label[t] = semi[t] = t;
        t++;
        for (auto v : graph[u]) {
        if (atob[v] == -1) dfs(v), par[atob[v]] = atob[u];
        trans[atob[v]].push_back(atob[u]);
        }
    };
    dfs(src);
    for (ll u = t - 1; u >= 0; --u) {
        for (auto v : trans[u]) semi[u] = min(semi[u], semi[find(v, 0)]);
        if (u) buck[semi[u]].push_back(u);
        for (auto w : buck[u]) {
        ll v = find(w, 0);
        dom[w] = semi[v] == semi[w] ? semi[w] : v;
        }
        if (u) link[u] = par[u];
    }
    v64 ret(n, -1);
    for (ll u = 1; u < t; ++u) {
        if (dom[u] != semi[u]) dom[u] = dom[dom[u]];
        ret[btoa[u]] = btoa[dom[u]];
    }
    return ret;
}

int main() {
    _;
    ll n, m;
    cin >> n >> m;
    vector<v64> adj(n);
    forn(i, 0, m) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
    }

    v64 dom = DomTree(adj, 0);

    v64 ans;
    for (ll u = n - 1; u != -1; u = dom[u]) ans.push_back(u);
    sort(ans.begin(), ans.end());

    cout << sz(ans) << ln;
    for (auto u : ans) cout << u + 1 << ' ';
    return 0;
}