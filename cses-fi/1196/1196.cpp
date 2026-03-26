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
// const ll INF = 100;

// Dijkstra's Shortest Paths
//
// Computes single-source shortest paths on non-negative weighted graphs using a priority queue.
//
// complexity: O((N + M) log N), O(N + M)

// d = distance | p = from/path
bool ajeita(ll val, v64& vec, ll k){
    ll idx = -1;
    forn(i,0,k) if(vec[i] > val){
        idx = i;
        break;
    }

    if(idx == -1) return false;
    for(ll i = k-1; i >= idx; i--){
        if(i > 0) vec[i] = vec[i-1];
    }
    vec[idx] = val;
    return true;
}

void dijkstra(ll s,ll k, vector<v64> &d, vector<vector<p64>>& g) {
    ll n = sz(g);
    d.assign(n, v64(k, INF));
    v64 vis(n);

    forn(i,0,k) d[s][i] = 0;
    priority_queue<tuple<ll,ll>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d_u, u] = pq.top();
        d_u  *= -1;
        pq.pop();
        if(vis[u] >= k) continue;
        vis[u]++;
        for (auto [v, w_v] : g[u]) {
            ajeita(d_u + w_v, d[v], k);
            pq.push({-(d_u+w_v), v});
        }
        trace(
            cout << "-> " << u << ln;
            forn(i,0,n){
                cout << i << ": ";
                forn(j,0,k){
                    cout << setw(4) << d[i][j] << " ";
                }
                cout << ln;
             }
        )
    }
}


int main() {
    _;
    ll n, m, k; cin >> n >> m >> k;
    vector<vector<p64>> g(n);
    forn(i,0,m){
        ll a, b, c; 
        cin >> a >> b >> c;
        a--, b--;
        g[a].push_back({b,c});
    }
    vector<v64> d;
    dijkstra(0, k, d, g);


    v64 vec = {1,2,3,5,6};
    debugv(vec);
    ajeita(4, vec, 5);
    debugv(vec);

    forn(i,0,k) cout << d[n-1][i] << " \n"[i==k-1];
    return 0;
}
