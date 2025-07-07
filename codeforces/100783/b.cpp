#include <bits/stdc++.h>
using namespace std;


typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ 42
    #define debug(x) cout << __LINE__ << ": "<< #x << " = " << x << ln;
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) 42
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;
vector<vector<p64>> g;

void dij(ll s, v64& d, vector<set<ll>>&p) {
    ll n = g.size();
    d.assign(n, INF);
    p.assign(n, {});

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
                p[v] = {u};
                pq.push({-d[v], v});
            } else if (d[u] + w_v == d[v]) {
                p[v].insert(u);
            }
        }
    }
}

int main() {
    _;
    ll n, m; cin >> n >> m;
    g.resize(n);
    map<p64, ll> counter;
    map<p64, ll> edges;
    forn(i, 0, m) {
        ll a, b, c; cin >> a >> b >> c;
        if (a > b) swap(a, b);

        if (!counter[{a,b}]) {
            counter[{a, b}] = 1;
            edges[{a, b}] = c;
        } else if (c < edges[{a, b}]) {
            edges[{a, b}] = c;
            counter[{a, b}] = 1; 
        } else if (c == edges[{a, b}]) {
            counter[{a, b}]++;
        }
    }

    for (auto [key, val] : edges) {
        g[key.first].emplace_back(key.second, val);
        g[key.second].emplace_back(key.first, val);
    }

    v64 d;
    vector<set<ll>> p;
    dij(0, d, p);

    ll ans= 0;

    v64 visited(n);
    function<void (ll)> dfs = [&](ll u) {
        visited[u] = true;
        for(auto v: p[u]) {
            ll aux1, aux2;
            aux1 = min(u, v);
            aux2 = max(u, v);
            ans += 2*edges[{aux1, aux2}]*counter[{aux1, aux2}];
            if (visited[v]) continue;
            dfs(v);
        }
    };

    dfs(n-1);

    cout << ans << ln;

    return 0;
}