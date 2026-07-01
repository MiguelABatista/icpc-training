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



int main() {
    _;
    ll n; cin >> n;
    vector<vll> g(n);
    forn(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vll treesum(n);
    vll subsize(n);

    function<ll (ll, ll)> dfs = [&](ll u, ll p){
        ll sum = 0;
        ll size = 0;
        for(ll v: g[u]){
            if(v == p) continue;
            sum += dfs(v,u);
            sum += subsize[v];
            size += subsize[v];
        }
        subsize[u] = size + 1;
        return sum;
    };
    
    treesum[0] = dfs(0,-1);
    // forn(i,0,n) treesum[i] = dfs(i,-1);
    // forn(i,0,n) cout << treesum[i] << " \n"[i==n-1];
    
    function<void (ll, ll)> dfs2 = [&](ll u, ll p){
        if(p != -1){
            treesum[u] = treesum[p] - subsize[u] + (n - subsize[u]);
        }
        for(ll v: g[u]){
            if(v == p) continue;
            dfs2(v,u);            
        }
    };

    dfs2(0,-1);
    forn(i,0,n) cout << treesum[i] << " \n"[i==n-1];

    return 0;
}
