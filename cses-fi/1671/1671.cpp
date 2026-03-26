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
    vector<vector<p64>> g(n);

    forn(i,0,m){
        ll a, b, c; cin >> a >> b >> c;
        a--, b--;
        g[a].push_back({b,c});
    }

    v64 d,p ;

    dijkstra(0,d,p,g);
    forn(i,0,n) cout << d[i] << " \n"[i==n-1];
    return 0;
}
