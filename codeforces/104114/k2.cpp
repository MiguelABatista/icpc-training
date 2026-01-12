#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto u : v) cout<< u << " "; cout << ln;})
#define debugm(v) trace({cout << #v": "; for (auto u : v) cout<< u.first << ":" << u.second << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

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


int main(){
    _;
    ll n, m, q; cin >> n >> m >> q;
    g.resize(n);
    
    forn(i,0,m){
        ll a, b, w;
        cin >> a >> b >> w;
        a--,b--;
        g[a].push_back({b,w});
        g[b].push_back({a,w});
    }


    forn(iiiiiii,0,q){
        ll a, b; cin >> a >> b;
        a--, b--;
        if(a > b) swap(a,b);

        v64 d(n), p(n);
        dijkstra(a,d,p);
        cout << (d[b]  >= INF ? -1 : d[b]) << ln;
    }
    
    return 0;
}