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

struct sparse {
    vector<v64> m;
    
    sparse(v64& v) {
        ll n = sz(v);
        ll logn = 64 - __builtin_clzll(n - 1);
        m.resize(n+1, v64(logn+1));

        forn(i, 0, n) m[i][0] = v[i];

        for (ll j = 1; (1 << j) <= n; j++)
        for (ll i = 0; i + (1 << j) <= n; i++)
            m[i][j] = min(m[i][j-1], m[i + (1 << (j-1))][j-1]);    
    }
    
    ll query(ll a, ll b) { 
        ll j = __builtin_clzll(1) - __builtin_clzll(b - a + 1);
        return min(m[a][j], m[b - (1 << j) + 1][j]);
    }
};

struct LCA {
	ll T = 0;
	v64 time, path, ret, dep;
	sparse rmq;

	LCA(vector<v64>& C) : time(sz(C)), dep(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<v64>& C, ll v, ll par) {
		time[v] = T++;
        if(par != -1) dep[v] = dep[par] + 1;
		for (ll y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	ll lca(ll a, ll b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b-1)];
	}
	ll dist(ll a,ll b){return dep[a] + dep[b] - 2*dep[lca(a,b)];}
};


int main() {
    _;
    ll n, q; cin >> n >> q;
    vector<v64> g(n);

    forn(i,0,n-1){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b); 
        g[b].push_back(a); 
    }

    LCA lca(g);

    forn(i,0,q){
        ll a, b; cin >> a >> b;
        a--; b--;
        cout << lca.dist(a, b) << ln;
    }
    return 0;
}
