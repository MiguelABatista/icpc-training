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

#define debug(u) trace(cout << __LINE__ << ": " #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << setw(2) << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll LOG = 20;

// LCA com Euler tour + Sparse Table (RMQ)
//
// Constroi com o grafo (lista de adjacencia) e a raiz 0
// Assume arvore enraizada em 0
//
// Complexidades:
// build - O(n log(n))
// lca - O(1)
// dist - O(1)

// Sparse Table (Idempotent Range Query)
//
// Preprocesses static array to answer idempotent range queries (e.g., min/max) in O(1) after O(N log N) build.
//
// complexity: O(N log N) build, O(1) query; O(N log N) space

struct sparse {
    vector<vll> m;
    
    sparse(vll& v) {
        ll n = sz(v);
        ll logn = 64 - __builtin_clzll(n - 1);
        m.resize(n+1, vll(logn+1));

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
	vll time, path, ret, dep;
	sparse rmq;

	LCA(vector<vll>& C, ll root) : time(sz(C)), dep(sz(C)), rmq((dfs(C,root,-1), ret)) {}
	void dfs(vector<vll>& C, ll v, ll par) {
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


// Block-Cut Tree
//
// Cria a block-cut tree, uma arvore com os blocos
// e os pontos de articulacao
// Blocos sao componentes 2-vertice-conexos maximais
// Uma 2-coloracao da arvore eh tal que uma cor sao
// os blocos, e a outra cor sao os pontos de art.
// Funciona para grafo nao conexo
//
// art[i] responde o numero de novas componentes conexas
// criadas apos a remocao de i do grafo g
// Se art[i] >= 1, i eh ponto de articulacao
// 
// Para todo i < blocks.size()
// blocks[i] eh uma componente 2-vertice-conexa maximal
// edgblocks[i] sao as arestas do bloco i
// tree[i] eh um vertice da arvore que corresponde ao bloco i
// 
// pos[i] responde a qual vertice da arvore vertice i pertence
// Arvore tem no maximo 2n vertices
//
// O(n+m)

struct block_cut_tree {
	vector<vector<ll>> g, blocks, tree;
	vector<vector<pair<ll, ll>>> edgblocks;
	stack<ll> s;
	stack<pair<ll, ll>> s2;
	vector<ll> id, art, pos;
	
	block_cut_tree(vector<vector<ll>> g_) : g(g_) {
		ll n = g.size();
		id.resize(n, -1), art.resize(n), pos.resize(n);
		build();
	}

	ll dfs(ll i, ll& t, ll p = -1) {
		ll lo = id[i] = t++;
		s.push(i);	
		
		if (p != -1) s2.emplace(i, p);
		for (ll j : g[i]) if (j != p and id[j] != -1) s2.emplace(i, j);
		
		for (ll j : g[i]) if (j != p) {
			if (id[j] == -1) {
				ll val = dfs(j, t, i);
				lo = min(lo, val);

				if (val >= id[i]) {
					art[i]++;
					blocks.emplace_back(1, i);
					while (blocks.back().back() != j) 
						blocks.back().push_back(s.top()), s.pop();

					edgblocks.emplace_back(1, s2.top()), s2.pop();
					while (edgblocks.back().back() != pair(j, i))
						edgblocks.back().push_back(s2.top()), s2.pop();
				}
				// if (val > id[i]) aresta i-j eh ponte
			}
			else lo = min(lo, id[j]);
		}
		
		if (p == -1 and art[i]) art[i]--;
		return lo;
	}

	void build() {
		ll t = 0;
		for (ll i = 0; i < g.size(); i++) if (id[i] == -1) dfs(i, t, -1);
		
		tree.resize(blocks.size());
		for (ll i = 0; i < g.size(); i++) if (art[i]) 
			pos[i] = tree.size(), tree.emplace_back();

		for (ll i = 0; i < blocks.size(); i++) for (ll j : blocks[i]) {
			if (!art[j]) pos[j] = i;
			else tree[i].push_back(pos[j]), tree[pos[j]].push_back(i);
		}
	}
};

void printbct(block_cut_tree& bct){
    auto& tree = bct.tree;
    auto& blocks = bct.blocks;
    auto& id =  bct.id;
    auto& art =  bct.art;
    auto& pos =  bct.pos;
    cout << "tree: \n"; 
    forn(i,0,sz(tree)){
        cout << i << " -> ";
        for(ll v: tree[i]) cout << v << " ";
        cout << ln;
    }
    cout << "blocks: \n"; 
    forn(i,0,sz(blocks)){
        cout << i << " -> ";
        for(ll v: blocks[i]) cout << v << " ";
        cout << ln;
    }
    cout << "------------ \n";
    cout << " id: "; forn(i,0,sz(id )) cout << setw(2) <<  id[i] << " \n"[i==sz(id )-1];
    cout << "art: "; forn(i,0,sz(art)) cout << setw(2) << art[i] << " \n"[i==sz(art)-1];
    cout << "pos: "; forn(i,0,sz(pos)) cout << setw(2) << pos[i] << " \n"[i==sz(pos)-1];
}

int main() {
    _;
    ll n, m, q; cin >> n >> m >> q;
    vector<vll> g(n);
    map<pll, ll> edges;

    forn(i,0,m){
        ll a, b, w; cin >> a >> b >> w;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
        edges[{a,b}] = w;
        edges[{b,a}] = w;
    }

    block_cut_tree bct(g);
    trace(printbct(bct);)

    ll root = sz(bct.blocks);
    auto& tree = bct.tree;
    ll nt = sz(tree);
    debug(nt);
    vll inv(nt);
    vll pai(nt);
    vll invblock(nt);
    vll h(nt);
    vll pref(n, -9);
    vector<vector<pll>> bl(LOG, vector<pll>(nt));
    LCA lca(tree, root);
    
    forn(i,0,n) inv[bct.pos[i]] = i;
    
    function<void (ll, ll)> dfs = [&](ll u, ll p){
        debug(u);
        pai[u] = p;
        h[u] = 1 + (p == -1 ? -1 : h[p]);
        for(ll v: tree[u]){
            if(v == p) continue;
            dfs(v,u);
        }
    };

    dfs(root, -1);
    ll cnt = 0;
    for(auto& block : bct.blocks){
        ll t = sz(block);
        if(t == 2) continue;
        debugv(block);
        forn(i,0,t) pref[block[i]] = 0;

        forn(i,0,t){
            invblock[block[i]] = cnt;
            pref[block[i]] = (i == 0 ? 0 : pref[block[i-1]]) + edges[{block[i], block[(i+1)%t]}];
        }
        cnt++;
    }
    

    auto getdist = [&](ll u, ll p){
        if(p == -1) return 0ll;
        if(u < root){ // u é um bloco;
            return 0ll;
        }
        if(p < root){ // p é bloco
            if(sz(bct.blocks[p]) == 2){
                return edges[{bct.blocks[p][0], bct.blocks[p][1]}];
            }

            ll pp = pai[p];
            ll tot = bct.blocks[p].back();   
            ll a = inv[pp];
            ll b = inv[u];
            ll delta = abs(pref[a]-pref[b]);
            ll dist = min(tot, tot-delta);
            return dist;
        }
        // ambos u e p são art
        return edges[{bct.pos[u],bct.pos[p]}]; 
    };
    
    auto cirdist = [&](ll a, ll b){
        ll tot = bct.blocks[invblock[a]].back();   
        ll delta = abs(pref[a]-pref[b]);
        ll dist = min(tot, tot-delta);
        return dist;
    };

    forn(i,0,nt) bl[0][i] = {pai[i], getdist(i,pai[i])};

    forn(j,1,LOG){
        forn(i,0,nt){
            ll x = bl[j-1][i].first;
            if(x == -1){
                bl[j][i] = bl[j-1][i];
                continue;
            }
            ll d = bl[j-1][i].second + bl[j-1][x].second;
            ll p = bl[j-1][x].first;
            bl[j][i] = {p,d};
        }
    }
    
    debug(root);
    debugv(pai);
    debugv(pref);
    trace(cout << "\n\n\n";)
    
    trace(
        forn(j,0,5){
            cout << j << ": ";
            forn(i,0,nt) cout << "{" << setw(3) << bl[j][i].first << ":" << setw(3) << bl[j][i].second << "}" << " ";
            cout << ln;
        }
    )

    while(q--){
        ll a, b; cin >> a >> b;
        a--, b--;
        ll aa = a;
        ll bb = b;
        a = bct.pos[a];
        b = bct.pos[b];
        ll resp = 0;
        
        if(invblock[a] == invblock[b]){
            cout << cirdist(aa,bb) << ln;
            continue;
        }
        
        if(h[a] < h[b]){
            swap(a,b);
            swap(aa,bb);
        }

        if(a < root){ // a block
            ll pa = pai[a];
            ll aux = inv[pa];
            resp += cirdist(aux, aa);
            a = pa;
        }

        debug(aa);
        debug(bb);
        debug(a);
        debug(b);
        
        for(ll exp = LOG-1; exp >= 0; exp--){
            ll pot = (1<<exp);
            if(h[a]-pot > h[b]){
                resp += bl[exp][a].second;
                a = bl[exp][a].first;
            }
        }

        debug(resp);
        
        if(b == pai[a]){
            if(b >= root){ // b é art, não tem problema
                resp += bl[0][a].second;
                cout << resp << ln;
                continue; // segue pra proxima query
            }

            // a é um art e b é um ciclo, a \in b
            aa = inv[a];

            resp += cirdist(aa,bb);
            cout << resp << ln;
            continue;
        }
        
        if(b < root){ // b block 
            ll pb = pai[b];
            ll aux = inv[pb];
            resp += cirdist(aux, bb);
            b = pb;
        }

        while(h[a] > h[b]){ // isso aqui pode rodar 0 1 ou 2 vezes (eu acho)
            resp += bl[0][a].second;
            a = bl[0][a].first;
        }

        if(a == b){
            cout << resp << ln;
            continue;
        }

        // h[a] == h[b]
        for(ll exp = LOG-1; exp >= 0; exp--){
            if(bl[exp][a].first != bl[exp][b].first){
                resp += bl[exp][a].second;
                resp += bl[exp][b].second;
                a = bl[exp][a].first;
                b = bl[exp][b].first;
            }
        }
        
        // nesse momento pai[a] = pai[b]
        ll p = pai[a];
        assert(pai[b] == p);

        if(p >= root){
            resp += bl[0][a].first;
            resp += bl[0][b].second;
            cout << resp << ln;
            continue;
        }
        
        aa = inv[a];
        bb = inv[b];
        debug(p);
        auto v=  bct.blocks[p];
        ll tot = bct.blocks[p].back();   
        
        ll delta = abs(pref[aa]-pref[bb]);
        ll dist = min(tot, tot-delta);
        resp += dist;
        cout << resp << ln;
        trace(cout << "-----------\n\n";)
    }


    return 0;
}
