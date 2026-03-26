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
 
pair<bool,v64> bellman_ford(ll s, ll n, v64& d, v64& p, vector<tuple<ll,ll,ll>> edges) {
    d.assign(n, INF);
    p.assign(n, -1);
    d[s] = 0;
    ll last = -1;

    forn(i, 0, n+1){
        last = -1;
        for (auto [u, v, w] : edges) {
            ll nd = d[u] + w;
            if (nd < d[v]) {
                p[v] = u;
                d[v] = nd;
                last = v;
            }
        }
    }

    if(last == -1) return {false, {}};
    ll curr = last;
    forn(i,0,n) curr = p[curr];
    v64 cic;
    ll start = curr;
    do{
        cic.push_back(curr);
        curr = p[curr];
    }while(curr != start);
    reverse(cic.begin(), cic.end());
    return {true, cic};
}
 
 
int main() {
    _;
    ll n, m; cin >> n >> m;
    vector<tuple<ll,ll,ll>> edges(m);
    forn(i,0,m){
        ll a, b, c; cin >> a >> b >> c;
        a--, b--;
        edges[i] = {a,b,c};
    }
    v64 d, p;
    auto [b,cic] = bellman_ford(0,n,d,p,edges);
    debugv(d);

    if(!b){
        cout << "NO" << ln;
        return 0;
    }
    cout << "YES" << ln;
    for(ll x : cic) cout << x + 1 << " ";
    cout << cic[0]+1 << ln;
    return 0;
}