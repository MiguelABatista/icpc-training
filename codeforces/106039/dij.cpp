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

void dijkstra(ll s, v64& d, v64& p){
    ll n = g.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;
    priority_queue<p64> pq;
    pq.push({0,s});
    while(!pq.empty()){
        ll u = pq.top().second;
        ll d_u = -pq.top().first;
        pq.pop();

        if(d_u != d[u]) continue;

        for (auto edge: g[u]){
            ll v = edge.first;
            ll w_v = edge.second;

            if(d[u] + w_v < d[v]) {
                d[v] = d[u] + w_v;
                p[v] = u;
                pq.push({-d[v],v});
            }
        }
    }
}



int main() {
    _;
    return 0;
}