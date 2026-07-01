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
const ll LOG = 20;

int main() {
    _;
    ll n, q; cin >> n >> q;
    vector<vll> bl(LOG, vll(n)); // bl[exp][i] o pai 2 ^exp de i
    vll h(n);
    vector<vll> g(n);
    
    forn(i,1,n){
        ll a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    function<void (ll, ll)> dfs = [&](ll u, ll p){
        if(p != -1){
            h[u] = h[p] + 1;
            bl[0][u] = p;
        }else{
            bl[0][u] = -2;
        }

        for(ll v: g[u]){
            if(v == p) continue;
            dfs(v,u);
        }
    };

    dfs(0,-1);

    forn(j,1,LOG){
        forn(i,0,n){
            ll x = bl[j-1][i];
            if(x == -2){
                bl[j][i] = -2;
            }else{
                bl[j][i] = bl[j-1][x];
            }
        }
    }

    while(q--){
        ll x, y; cin >> x >> y;
        x--, y--;
        ll xx = x;
        ll yy = y;

        if(h[x] < h[y]) swap(x,y);

        for(ll exp = LOG-1; exp >= 0; exp--){
            ll pot = 1<<exp; 
            if(h[x] - pot >= h[y]){
                x = bl[exp][x];
            }
        }


        for(ll exp = LOG-1; exp >= 0; exp--){
            if(bl[exp][x] != bl[exp][y]){
                x = bl[exp][x];
                y = bl[exp][y];
            }
        }
        // x e o y vão ter o msm pai imediato.
        ll lca = x == y ? x : bl[0][x];
        cout << h[xx]-h[lca] + h[yy] - h[lca] << ln;
    }
}
