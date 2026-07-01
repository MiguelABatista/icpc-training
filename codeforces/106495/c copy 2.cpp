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
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << setw(2) << xx.first << ":" << setw(2) << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll LOG = 20;

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
    vll inv(nt);
    vll pai(nt);
    vll invblock(n,-1);
    vll h(nt);
    vector<map<ll,ll>> blockmp(root);
    vector<vll> blockpref(root);

    vector<vector<pll>> bl(LOG, vector<pll>(nt));

    forn(i,0,n) inv[bct.pos[i]] = i;
    
    function<void (ll, ll)> dfs = [&](ll u, ll p){
        pai[u] = p;
        h[u] = 1 + (p == -1 ? -1 : h[p]);
        for(ll v: tree[u]){
            if(v == p) continue;
            dfs(v,u);
        }
    };

    dfs(root, -1);
    ll cnt = -1;
    for(auto& block : bct.blocks){
        cnt++;
        ll t = sz(block);
        blockpref[cnt].resize(t+1);
        forn(i,0,t){
            if(t > 2) invblock[block[i]] = cnt;
            blockmp[cnt][block[i]] = i;
            blockpref[cnt][i] = (i == 0 ? 0 : blockpref[cnt][i-1] + edges[{block[i],block[i-1]}]);
        }
        blockpref[cnt][t] = blockpref[cnt][t-1] + edges[{block[0],block[t-1]}];
    }

    // debugv(invblock);

    auto cirdist = [&](ll a, ll b, ll circ){
        if(sz(bct.blocks[circ]) == 2) return edges[{a,b}];
        auto& pref = blockpref[circ];
        ll tot = pref.back(); 
        ll idxa = blockmp[circ][a];
        ll idxb = blockmp[circ][b];
        tie(idxa, idxb) = minmax(idxa, idxb);
        
        ll delta = pref[idxb] - (idxa == 0 ? 0 : (pref[idxa-1]));
        delta = abs(delta);
        debug(circ);
        debugv(pref);
        debug(idxa);
        debug(idxb);
        debug(tot);
        debug(delta);

        ll dist = min(delta, tot-delta);
        return dist;
    };

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
            ll a = inv[pp];
            ll b = inv[u];
            return cirdist(a,b, p);
        }
        // ambos u e p são art
        return edges[{bct.pos[u],bct.pos[p]}]; 
    };
    

    // forn(i,0,n){
    //     forn(j,i+1,n){
    //         if(invblock[i] != invblock[j]) continue;
    //         if(invblock[i] == -1) continue;
    //         if(invblock[j] == -1) continue;
    //         cout << i << " " << j << " " << cirdist(i,j, invblock[i]) << ln;
    //     }
    // }

    // trace(
    //     forn(i,0,root){
    //         cout << i << ": "; for(ll x: blockpref[i]) cout << x << " ";; cout << ln;
    //     }
    // )
    // // trace(cout << "numm: "; forn(i,0,n) cout << setw(2) << i%10 << " ";; cout << ln;)

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
    
    // debug(root);
    // debugv(pai);
    // trace(cout << "\n\n\n";)
    
    // trace(
    //     forn(j,0,5){
    //         cout << j << ": ";
    //         forn(i,0,nt) cout << "{" << setw(3) << bl[j][i].first << ":" << setw(3) << bl[j][i].second << "}" << " ";
    //         cout << ln;
    //     }
    // )
    debugv(invblock);
    while(q--){
        ll a, b; cin >> a >> b;
        a--, b--;
        ll aa = a;
        ll bb = b;
        a = bct.pos[a];
        b = bct.pos[b];
        ll resp = 0;
        debug(a);
        debug(b);
        if(invblock[aa] == invblock[bb]){
            debug(1);
            cout << cirdist(aa,bb, invblock[a]) << ln;
            continue;
        }
        
        if(h[a] < h[b]){
            swap(a,b);
            swap(aa,bb);
        }else if(h[a] == h[b]){
            if(a < root){ // a block
               ll pa = pai[a];
                ll aux = inv[pa];
                resp += cirdist(aux, aa, a);
                a = pa;
                aa = -1;
            }
            if(b < root){
                ll pb = pai[b];
                ll aux = inv[pb];
                resp += cirdist(aux, bb, b);
                b = pb;
                bb = -1;
            }   
        }

        if(a < root && aa != -1){ // a block
            ll pa = pai[a];
            ll aux = inv[pa];
            resp += cirdist(aux, aa, a);
            a = pa;
        }


        for(ll exp = LOG-1; exp >= 0; exp--){
            ll pot = (1<<exp);
            if(h[a]-pot > h[b]){
                resp += bl[exp][a].second;
                a = bl[exp][a].first;
            }
        }


        if(b == pai[a]){
            if(b >= root){ // b é art, não tem problema
                resp += bl[0][a].second;
                cout << resp << ln;
                continue; // segue pra proxima query
            }

            // a é um art e b é um ciclo, a \in b
            aa = inv[a];

            resp += cirdist(aa,bb, 0);
            cout << resp << ln;
            continue;
        }
        
        // Sobe a pra h[a] == h[b];
        resp += bl[0][a].second;
        a = bl[0][a].first;

        if(b < root && bb != -1){
            ll pb = pai[b];
            ll aux = inv[pb];
            resp += cirdist(aux, bb, b);
            b = pb;
        }

        if(b == pai[a]){
            // sabemos que b é art, ent a é block
            resp += bl[0][a].second;
            cout << resp << ln;
            continue; // segue pra proxima query
        }

        // Sobe a pra h[a] == h[b];
        if(h[a] > h[b]){
            resp += bl[0][a].second;
            a = bl[0][a].first;
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
        resp += cirdist(aa,bb,p);
        cout << resp << ln;
        trace(cout << "-----------\n\n";)
    }


    return 0;
}
