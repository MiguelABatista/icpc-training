#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;
typedef vector<p64> vp64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

vector<vp64> adj; // (v, w)

// d = distance | p = path
void dijkstra(ll s, v64 &d, v64& p) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;
    priority_queue<p64, vp64, greater<p64>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        ll u = pq.top().second;
        ll d_u = pq.top().first;
        pq.pop();

        if (d_u != d[u]) continue;

        for (auto edge : adj[u]) {
            ll v = edge.first;
            ll w_v = edge.second;

            if (d[u] + w_v < d[v]) {
                d[v] = d[u] + w_v;
                p[v] = u;
                pq.push({d[v], v});
            }
        }
    }
}

int main(){
    _; ll n, m, min_cost = 0; cin >> n >> m;

    vector<ll> peso_vert(n);
    adj.resize(n);

    forn(i, 0, n) cin >> peso_vert[i];

    forn(i, 0, m){
        ll a, b, c; cin >> a >> b >> c;
        adj[a-1].push_back({b-1, c});
        adj[b-1].push_back({a-1, c});
    }

    v64 d, p;
    dijkstra(0, d, p);

    forn(i,0,n){
        min_cost += d[i]*peso_vert[i];
    }
    cout << min_cost << ln;
    return 0;
}