#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for(ll i=s; i<e; i++)
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
#define debugv(v) trace(cout << #v ": " ;for(auto xx : v) cout << xx << " ";cout << ln)
#define debugm(v) trace(cout << #v ": " ;for(auto xx : v) cout << xx.first << ":" << xx.second << " ";cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void dij(ll s, vll& d, vector<vector<pll>>& g){
    ll n = sz(g);
    d.assign(n, INF);

    d[s]= 0;
    priority_queue<pll> pq;

    pq.push({0,s});
    while(!pq.empty()){
        ll u = pq.top().second;
        ll d_u = -pq.top().first;
        pq.pop();
        if(d_u != d[u]) continue;

        for(auto [v, w_v] : g[u]){
            if(d[u] + w_v < d[v]){
                d[v] = d[u] + w_v;
                pq.push({-d[v], v});
            }
        }
    }
}


int main(){
    _;
    ll n, m, k; cin >> n >> m >> k;

    vector<vector<pll>> g((k+1)*n);  
    // vertice i i+n i+2*n ... i+k*n são o msm

    forn(i,0,m){
        ll a, b, f, w; 
        cin >> a >> b >> f >> w;
        a--; b--;
        forn(j,0,k+1){
            g[a+j*n].push_back({b+j*n,f});
            g[b+j*n].push_back({a+j*n,f});
            if(j != k && w != -1){
                g[a+j*n].push_back({b+(j+1)*n,w});
                g[b+j*n].push_back({a+(j+1)*n,w});
            }
        }
    }

    vll d;
    dij(0, d, g);
    forn(i,0,(k+1)*n){
        debug(i);
        debugm(g[i]);
    }

    ll resp = INF;
    forn(i,0,k+1) if(d[n-1+i*n] != -1) resp = min(resp, d[n-1+i*n]);
    cout << resp << ln;
    return 0;
} 