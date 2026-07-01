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

    vector<vll> bl(LOG, vll(n));
    vector<vll> g(n);
    vll h(n);

    bl[0][0] = -2;

    forn(i,1,n){
        ll p; cin >> p;
        p--;
        bl[0][i] = p;
        g[i].push_back(p);
        g[p].push_back(i);
    }

    function<void (ll, ll)> dfs = [&](ll u, ll p){
        if(p != -1) h[u] = h[p]+1;
        for(ll v : g[u]){
            if(v == p) continue;
            dfs(v,u); 
        }

    };

    dfs(0,-1);

    forn(i,1,LOG){
        forn(j,0,n){
            ll x = bl[i-1][j];
            if(x == -2) bl[i][j] = -2;
            else  bl[i][j] = bl[i-1][bl[i-1][j]];
        }
    }

    while(q--){
        ll x, y;
        cin >> x >> y;
        x--, y--;
        if (h[x] < h[y]){
            swap(x,y);
        }

        
        for(ll exp = LOG-1; exp >= 0; exp--){
            ll pot = 1<<exp;
            if(h[x]-pot >= h[y]){
                x = bl[exp][x];
            }            
        }

        for(ll exp = LOG-1; exp >= 0; exp--){
            if(bl[exp][x] != bl[exp][y]){
                x = bl[exp][x];
                y = bl[exp][y];
            }            
        }
        ll lca = (x == y) ? x : bl[0][x];
        cout << lca+1 << ln;
    }

    return 0;
}
