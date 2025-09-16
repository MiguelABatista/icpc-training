#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

vector<vector<p64>> g;
vector<vector<p64>> v_to_cor;
vector<v64> cor_to_v;
ll n, m, k;

void dijkstra(ll s, v64& d){
    d.assign(n, INF);
    vector<bool> vis_cor(k, false);

    d[s] = 0;

    priority_queue<p64> pq;
    priority_queue<p64> pq_cor;

    pq.push({0,s});

    for(auto [cor, cost] : v_to_cor[0]){
        pq_cor.push({-cost, cor});

    }

    while(!pq.empty() || !pq_cor.empty() ){
        // forn(i,0,n){ cout << d[i] << " ";} cout << ln;
        ll u = -1;
        ll d_u = INF;
        ll c = -1;
        ll d_c = INF;

        if(!pq.empty()){
            u = pq.top().second;
            d_u = -pq.top().first;
        }
        if(!pq_cor.empty()){   
            c = pq_cor.top().second;
            d_c = -pq_cor.top().first;
        }

        if(d_c < d_u){
            pq_cor.pop();
            if(vis_cor[c]) continue;
            debug("COR");
            debug(c);
            debug(d_c);

            vis_cor[c] = true;

            for(ll v : cor_to_v[c]){
                if(d_c < d[v]){
                    d[v] = d_c;
                    pq.push({-d_c, v});
                }
            }
            continue;
        }

        pq.pop();
        if(d_u != d[u]) continue;

        debug("PATH");
        debug(u);
        debug(d_u);

        for(auto [cor, cost] : v_to_cor[u]){
            pq_cor.push({-(d_u+cost), cor});
        }

        for (auto edge: g[u]){
            ll v = edge.first;
            ll w_v = edge.second;

            if(d[u] + w_v < d[v]) {
                d[v] = d[u] + w_v;
                pq.push({-d[v],v});
            }
        }
    }
}

int main() {
    _;
    cin >> n >> m >> k;

    v_to_cor.resize(n);
    cor_to_v.resize(k); 
    g.resize(n);

    forn(i,0,m){
        ll a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].emplace_back(b,c);
        g[b].emplace_back(a,c);
    }

    forn(i,0,n){
        ll c; cin >> c;
        forn(j,0,c){
            ll tep, cost;
            cin >> tep >> cost;
            tep--;
            v_to_cor[i].emplace_back(tep, cost);
            cor_to_v[tep].push_back(i);
        }
    }

    v64 d;
    dijkstra(0, d);

    // forn(i,0,n){ cout << d[i] << " ";} cout << ln;
    cout << d[n-1] << ln;
    return 0;
}