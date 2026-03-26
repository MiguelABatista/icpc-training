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

void bellman_ford(ll s, ll n, v64& d, v64& p, vector<tuple<ll,ll,ll>> edges) {
    d.assign(n, INF);
    p.assign(n, -1);
    d[s] = 0;

    sort(edges.begin(), edges.end(), [](auto& a, auto& b) {
        ll sa = get<0>(a) < get<1>(a) ? get<0>(a) : -get<0>(a);
        ll sb = get<0>(b) < get<1>(b) ? get<0>(b) : -get<0>(b);
        return sa < sb;
    });

    ll lim = n / 2 + 2; // use n-1 with unsorted edges
    forn(i, 0, lim) for (auto [u, v, w] : edges) {
        if (d[u] == INF || d[u] == -INF) continue;
        ll nd = d[u] + w;
        if (nd < d[v]) {
            p[v] = u;
            d[v] = (i < lim - 1 ? nd : -INF);
        }
    }
    forn(i, 0, lim) for (auto [u, v, w] : edges)
        if (d[u] == -INF) d[v] = -INF;
}


int main() {
    _;
    ll n, m; cin >> n >> m;
    vector<tuple<ll,ll,ll>> edges(m);
    forn(i,0,m){
        ll a, b, c; cin >> a >> b >> c;
        a--, b--;
        edges[i] = {a,b,-c};
    }
    v64 d, p;
    bellman_ford(0,n,d,p,edges);
    cout << (d[n-1] == -INF ? -1 : -d[n-1]) << ln;
    return 0;
}
