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
ll n;
vector<vector<p64>> g;
vector<bool> valid;
vector<v64> a_to_b;
map<p64, ll> ans;


// Dijkstra's Shortest Paths
//
// Computes single-source shortest paths on non-negative weighted graphs using a priority queue.
//
// complexity: O((N + M) log N), O(N + M)

// d = distance | p = from/path
void dijkstra(ll s, v64 &d, ll l, ll r) {
    d.assign(n, INF);

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
            if(v < l || v > r) continue;
            ll w_v = edge.second;

            if (d[u] + w_v < d[v]) {
                d[v] = d[u] + w_v;
                pq.push({-d[v], v});
            }
        }
    }
}

void dnc(ll l, ll r){
    if(r <= l) return;
    ll mid = (l+r)/2;
    
    ll lmid = max(mid-4, l);
    ll rmid = min(r, mid+5);
    // mid-4 mid-3 mid-2 mid-1 mid mid+1 mid+2 mid+3 mid+4 mid+5

    vector<v64> ds(10);
    forn(i,lmid,rmid+1) dijkstra(i,ds[i-lmid], l-10, r+10);

    forn(a,l,lmid){
        if(a_to_b[a].empty()) continue;
        auto& bs = a_to_b[a]; 
        while(!bs.empty() && bs.back() > rmid){
            ll b = bs.back();
            bs.pop_back();
            ll best = INF;
            debug(a);
            debug(b);
            forn(i,lmid,rmid+1){
                forn(j,lmid,rmid+1){ 
                    ll idx = i-lmid;
                    ll jdx = j-lmid;
                    // a -> i -> j -> b
                    ll curr = ds[idx][a];
                    curr += ds[idx][j];
                    if(curr > INF) curr = INF;
                    curr += ds[jdx][b];
                    
                    if(curr > INF) curr = INF;
                    best = min(curr, best);
                }
            }
            ans[{a,b}] = best;
        }
    }

    forn(a,lmid,rmid+1){
        if(a_to_b[a].empty()) continue;
        auto& bs = a_to_b[a]; 
        while(!bs.empty() && bs.back() > mid){
            ll b = bs.back();
            bs.pop_back();
            ll best = INF;
            forn(i,lmid,rmid+1){
                forn(j,lmid,rmid+1){ 
                    ll idx = i-lmid;
                    ll jdx = j-lmid;
                    // a -> i -> j -> b
                    ll curr = ds[idx][a];
                    curr += ds[idx][j];
                    if(curr > INF) curr = INF;
                    curr += ds[jdx][b];
                    
                    if(curr > INF) curr = INF;
                    best = min(curr, best);
                }
            }
            ans[{a,b}] = best;
        }
    }
    dnc(l, lmid);
    dnc(rmid, r);
}

int main(){
    _;
    ll m, q; cin >> n >> m >> q;
    g.resize(n);
    a_to_b.resize(n);
    valid.resize(n);

    forn(i,0,m){
        ll a, b, w;
        cin >> a >> b >> w;
        a--,b--;
        g[a].push_back({b,w});
        g[b].push_back({a,w});
    }

    vector<p64> perg(q);

    forn(i,0,q){
        ll a, b; cin >> a >> b;
        a--, b--;
        if(a > b) swap(a,b);
        perg.push_back({a,b});
        a_to_b[a].push_back(b);
    }

    forn(i,0,n) sort(a_to_b[i].begin(), a_to_b[i].end());

    dnc(0,n-1);

    trace(
        cout << "LAMPREIA" << ln;
        cout << sz(ans) << ln;
        for(auto [p, v] : ans){
            cout << p.first << ":" << p.second << " " << v << ln;
        }
    );

    return 0;
}