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
const ll MOD = 1'000'000'007;

// Dijkstra's Shortest Paths
//
// Computes single-source shortest paths on non-negative weighted graphs using a priority queue.
//
// complexity: O((N + M) log N), O(N + M)

// d = distance | p = from/path
void dijkstra(ll s, v64 &d, v64& p, vector<vector<p64>>& g) {
    ll n = sz(g);
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

        for (auto [v, w_v] : g[u]) {
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
    ll n, m; cin >> n >> m;
    vector<vector<p64>> g2(n);
    vector<v64> g(n);
    vector<tuple<ll,ll,ll>> ed;
    forn(i,0,m){
        ll a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        ed.push_back({a,b, c});
        g2[a].push_back({b,c});
    }
    v64 p, d;
    dijkstra(0,d,p,g2);

    for(auto [a,b,c] : ed){
        if(d[a] + c > d[b]) continue;
        g[a].push_back(b);
    }

    v64 vis(n);
    v64 dp(n, -1);
    v64 minf(n, INF);
    v64 maxf(n, -INF);

    function<void (ll)> dfs = [&](ll u){
        debug(u);
        vis[u] = 1;
        ll amt = 0;
        ll mif = INF;
        ll maf = -INF;
        if(u == n-1){
            amt = 1;
            mif = 0;
            maf = 0;
        }

        for(ll v: g[u]){
            if(!vis[v]) dfs(v);
            amt = (amt+dp[v])%MOD;
            mif = min(minf[v], mif);
            maf = max(maxf[v], maf);
        }

        dp[u] = amt;
        if (u == n - 1) {
            minf[u] = 0;
            maxf[u] = 0;
        } else {
            minf[u] = mif + 1;
            maxf[u] = maf + 1;
        }
        return;
    };
    dfs(0);
    forn(i,0,n){debugv(g[i]);};
    debugv(dp);
    debugv(minf);
    debugv(maxf);
    cout << d[n-1] << " " << dp[0] << " " << minf[0] << " " << maxf[0] << ln;
    return 0;
}
