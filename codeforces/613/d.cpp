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
const ll MAX = 100'010;
const ll MAXLOG = 19;
vector<v64> g;

// LCA com HLD
//
// Assume que um vertice eh ancestral dele mesmo, ou seja,
// se a eh ancestral de b, lca(a, b) = a
// Para buildar pasta chamar build(root)
// anc(a, b) responde se 'a' eh ancestral de 'b'
//
// Complexidades:
// build - O(n)
// lca - O(log(n))
// anc - O(1)

// Sparse Table (Idempotent Range Query)
//
// Preprocesses static array to answer idempotent range queries (e.g., min/max) in O(1) after O(N log N) build.
//
// complexity: O(N log N) build, O(1) query; O(N log N) space

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

// LCA com Euler tour + Sparse Table (RMQ)
//
// Constroi com o grafo (lista de adjacencia) e a raiz 0
// Assume arvore enraizada em 0
//
// Complexidades:
// build - O(n log(n))
// lca - O(1)
// dist - O(1)

struct LCA {
	ll T = 0;
	v64 time, path, ret, dep;
	sparse rmq;

	LCA(vector<v64>& C, ll root) : time(sz(C)), dep(sz(C)), rmq((dfs(C,root,-1), ret)) {}
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

// Virtual Tree
//
// Comprime uma arvore dado um conjunto S de vertices, de forma que
// o conjunto de vertices da arvore comprimida contenha S e seja
// minimal e fechado sobre a operacao de LCA
// Se |S| = k, a arvore comprimida tem menos que 2k vertices
// As arestas de virt possuem a distancia do vertice ate o vizinho
// Retorna a raiz da virtual tree
// 
// lca::pos deve ser a ordem de visitacao no dfs
// voce pode usar o LCAcomHLD, por exemplo
//
// O(k log(k))

vector<pair<ll, ll>> virt[MAX];
vector<pair<ll, bool>> dp;   

void print(v64& v){
    for(ll x: v) cout << x << " ";
    cout << ln;
}

ll build_virt(vector<ll> v, LCA& lca) {
	auto cmp = [&](ll i, ll j) { return lca.time[i] < lca.time[j]; };
	sort(v.begin(), v.end(), cmp);
	for (ll i = v.size()-1; i; i--) v.push_back(lca.lca(v[i], v[i-1]));
	sort(v.begin(), v.end(), cmp);
    v.erase(unique(v.begin(), v.end()), v.end());
    forn(i,0,v.size()) virt[v[i]].clear();
	forn(i,1,v.size()) virt[lca.lca(v[i-1], v[i])].clear();
    forn(i,1,v.size()) {
		ll parent = lca.lca(v[i-1], v[i]);
		ll d = lca.dist(parent, v[i]);
// #warning soh to colocando aresta descendo
		virt[parent].emplace_back(v[i], d);
	}

	return v[0];
}

void dfs(ll u, ll p, set<ll>& esp){
    ll resp = 0;
    ll chega_na_raiz = 0;
    bool fui_tomada = false;
    bool u_esp = esp.count(u);

    for(auto [v,w] : virt[u]){
        if(v == p) continue;
        bool v_esp = esp.count(v);
        
        dfs(v,u, esp);
        
        if(dp[v].first == INF || ((w == 1) && u_esp && v_esp)){
            resp = INF;
            break;
        }

        resp += dp[v].first;

        if(dp[v].second){
            if(u_esp){
                resp++;
                continue;
            }

            if(fui_tomada) continue;

            if(chega_na_raiz == 0){
                chega_na_raiz = 1;
            }else{
                fui_tomada = true;
                resp++;
            }
        }
    }

    if(fui_tomada) chega_na_raiz = 0;
    if(u_esp) chega_na_raiz = 1;

    // cout << u << " " << resp << " " << chega_na_raiz << ln;
    dp[u] = {resp, (chega_na_raiz == 1)};
}

int main(){
    _;
    ll n; cin >> n;
    g.resize(n);
    dp.resize(n);
    forn(i,0,n-1){
        ll a, b; 
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    LCA lca(g, 0);
    ll q; cin >> q;
    
    v64 ver(n);
    set<ll> s;

    while(q--){
        ver.clear();
        s.clear();
        ll k; cin >> k;
        ver.resize(k);
        forn(i,0,k) cin >> ver[i], ver[i]--;
        ll r = build_virt(ver, lca);

        // forn(i,0,n){
        //     cout << virt[i].size() << ln;
        //     for(p64 p: virt[i]){
        //         cout << i << " " << p.first << " " << p.second << ln;
        //     }
        // }

        
        for(ll x: ver) s.insert(x);

        dfs(r, -1,s);
        cout << (dp[r].first == INF ? -1 : dp[r].first) << ln;
    }
    return 0; 
}
