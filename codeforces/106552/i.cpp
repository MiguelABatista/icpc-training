#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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
void dijkstra(ll s, vll &d, vector<vector<pll>>& g) {
    ll n = sz(g);
    d.assign(n, INF);

    d[s] = 0;
    priority_queue<pll> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        ll u = pq.top().second;
        ll d_u = -pq.top().first;
        pq.pop();

        if (d_u != d[u]) continue;

        for (auto [v, w_v] : g[u]) {
            if (d[u] + w_v < d[v]) {
                d[v] = d[u] + w_v;
                pq.push({-d[v], v});
            }
        }
    }
}


int main() {
    _;
    ll n, m, q; cin >> n >> m >> q;
    vector<vector<pll>> g(n+m);

    // 0, 1, ..., n-1 pessoas
    // n, n+1, n ... n+m-1 linguas

    forn(i,0,n){
        ll k; cin >> k;
        forn(j,0,k){
            ll x; cin >> x;
            x--;
            g[i].push_back({n+x,1});
            g[n+x].push_back({i,1});
        }
    }  

    vector<vll> d(m);
    forn(i,0,m) dijkstra(n+i, d[i], g);
    
    while (q--){
        ll a, b; cin >> a >> b;
        a--, b--;
        ll resp = INF;
        forn(i,0,m){
            debug(i);
            debug(d[i][a]);
            debug(d[i][b]);
            trace(cout << ln;)
            ll curr = d[i][a]/2 + d[i][b]/2;
            resp = min(resp, curr);
        }
        trace(cout << ln << ln;)
        if(resp > INF/3) resp = -1;
        cout << resp << ln;
    }
    
    return 0;
}
