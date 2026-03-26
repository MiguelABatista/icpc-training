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

// Centroid Tree
//
// Constroi a centroid tree
// p[i] eh o pai de i na centroid-tree
// dist[i][k] = distancia na arvore original entre i
// e o k-esimo ancestral na arvore da centroid
//
// O(n log(n)) de tempo e memoria

const ll MAX = 100'005;

// Custom Hash for hash table
//
// Provides 64-bit hashers for integers and pairs to use with __gnu_pbds::gp_hash_table.
//
// complexity: O(1) average, O(n)

#include <bits/extc++.h> 

struct ct{
    ll n;
    vector<v64> g, dist;
    v64 siz, rem, par;

    ll dfs_sz(ll i, ll p=-1) {
        siz[i] = 1;
        for (ll j : g[i]) if (j != p && !rem[j]) siz[i] += dfs_sz(j, i);
        return siz[i];
    }
    
    ll centroid(ll i, ll p, ll size) {
        for (ll j : g[i]) if (j != p && !rem[j] && siz[j] > size / 2)
        return centroid(j, i, size);
        return i;
    }
    
    void dfs_dist(ll i, ll p, ll d=0) {
        dist[i].push_back(d);
        for (ll j : g[i]) if (j != p && !rem[j])
        dfs_dist(j, i, d+1);
    }

    void decomp(ll i, ll p = -1) {
        ll c = centroid(i, i, dfs_sz(i));
        rem[c] = 1, par[c] = p;
        dfs_dist(c, c);
        for (ll j : g[c]) if (!rem[j]) decomp(j, c);
    }

    ct(ll tn, vector<v64>& tg) : n(tn), g(tg),
            dist(n), siz(n), rem(n), par(n){
        forn(i,0,n) rem[i] = 0, dist[i].clear();
        decomp(0);
        forn(i,0,n) reverse(dist[i].begin(), dist[i].end());
    }
};

int main() {
    _;

    ll n, k; cin >> n >> k;
    vector<v64> g(n);

    forn(i,0,n-1){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    ct cent(n, g);
    return 0;
    vector<v64> tree(n);
    v64 rem(n);
    v64 siz(n);
    v64 big(n);

    ll root = -1;
    forn(i,0,n){
        if(cent.par[i] == -1){
            root = i;
            continue;
        }
        tree[cent.par[i]].push_back(i);
    }
    
    function<ll (ll, ll)> dfssz = [&](ll u, ll p){
        ll resp = 1;
        ll best = 0;
        for(ll v: tree[u]){
            ll aux = dfssz(v,u);
            resp += aux;
            best = max(best, aux);
        }
        siz[u] = resp;
        big[u] = best;
        return resp;
    };

    dfssz(root, -1);

    function<void (ll ,ll,ll, v64&)> dfs = [&](ll u, ll p, ll d, v64& vec){
        if(d > k) return;   // prune here
        vec.push_back(d);
        for(ll v: g[u]){
            if(v == p)continue;
            if(rem[v]) continue;
            dfs(v, u, d+1, vec);
        }
        return;
    };

    function<ll (ll)> rec = [&](ll u){
        ll resp = 0;
        rem[u] = 1;

        v64 mptot(big[u]+1);
        v64 vec;
        for(ll v: tree[u]){
            dfs(v,u,1, vec);
            for(ll d : vec){
                if(k-d > big[u]) continue;
                resp += mptot[k-d];
            }
            for(ll d : vec) mptot[d]++;
            vec.clear();
        }

        if(k <= big[u]) resp += mptot[k];

        for(ll v : tree[u]){
            if(rem[v]) continue;
            resp += rec(v);
        }
        return resp;
    };
 

    cout << rec(root) << ln;
    return 0;   
}
