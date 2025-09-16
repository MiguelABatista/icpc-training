#include <bits/stdc++.h>
using namespace std;

typedef int ll;
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
const ll MAX = 100'010;
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

namespace lca{
    ll pos[MAX], h[MAX], sz[MAX];
    ll pai[MAX], t;
    ll dep[MAX];

    void build(ll k, ll p = -1, ll f = 1) {
        pos[k] = t++; sz[k] = 1; 
        if(p == -1) dep[k] = 0;
        for (ll& i : g[k]) if (i != p) {
            pai[i] = k;
            dep[i] = dep[k] + 1;
            h[i] = (i == g[k][0] ? h[k] : i);
            build(i, k, f); sz[k] += sz[i];
            
            if (sz[i] > sz[g[k][0]] or g[k][0] == p) swap(i, g[k][0]);
        }
        if (p*f == -1) t = 0, h[k] = k, build(k, -1, 0);
    }
    
    ll lca(ll a, ll b) {
        if (pos[a] < pos[b]) swap(a, b);
        return h[a] == h[b] ? b : lca(pai[h[a]], b);
    }
    
    bool anc(ll a, ll b) {
        return pos[a] <= pos[b] and pos[b] <= pos[a]+sz[a]-1;
    }

    ll dist(ll a, ll b){
        return dep[a] + dep[b] - 2*dep[lca(a,b)];
    }
}


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

// #warning lembrar de buildar o LCA antes
ll build_virt(vector<ll> v) {
	auto cmp = [&](ll i, ll j) { return lca::pos[i] < lca::pos[j]; };
	sort(v.begin(), v.end(), cmp);
	for (ll i = v.size()-1; i; i--) v.push_back(lca::lca(v[i], v[i-1]));
	sort(v.begin(), v.end(), cmp);
    v.erase(unique(v.begin(), v.end()), v.end());
    forn(i,0,v.size()) virt[v[i]].clear();
	forn(i,1,v.size()) virt[lca::lca(v[i-1], v[i])].clear();
    forn(i,1,v.size()) {
		ll parent = lca::lca(v[i-1], v[i]);
		ll d = lca::dist(parent, v[i]);
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
    
    lca::build(0);
    ll q; cin >> q;
    
    v64 ver(n);
    set<ll> s;

    while(q--){
        ver.clear();
        s.clear();
        ll k; cin >> k;
        ver.resize(k);
        forn(i,0,k) cin >> ver[i], ver[i]--;
        ll r = build_virt(ver);

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
