// Template Skeleton
//
// Sets up fast I/O, aliases, and basic macros for contests.

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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
const ll MAX = 100;

/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */


// Segment Tree (Range Query + Point Update)
//
// Balanced binary tree for range queries with a customizable combine; supports point updates and range queries.
//
// complexity: O(log N) per op, O(N)

struct lazy {
    ll add = 0;
    optional<ll> set;
    
    void compose(const lazy& o) {
        if (o.set.has_value()) {
            set = o.set;
            add = 0;
        }

        if (o.add != 0) {
            if (set.has_value()) *set += o.add;
            else add += o.add;
        }
    }
};

struct node {
    ll val = 0;
    
    static node comb(const node& a, const node& b) {
        return {max(a.val, b.val)};
    }

    void resolve(const lazy& lz, ll l, ll r) {
        if (lz.set.has_value()) val = *lz.set;
        if (lz.add) val += lz.add;
    }
};

const node neutral = {0};

struct tree {
    ll lm, rm;
    unique_ptr<tree> lc, rc;
    
    node val;
    lazy lz;

    tree(ll l_, ll r_, const vector<node>& v) : lm(l_), rm(r_) {
        if (lm == rm) val = v[lm];
        else {
            ll m = (lm + rm) / 2;
            lc = make_unique<tree>(lm, m, v);
            rc = make_unique<tree>(m + 1, rm, v);
            pull();
        }
    }

    void pull() {
        val = node::comb(lc->val, rc->val);
    }

    void push() {
        val.resolve(lz, lm, rm);
        if (lm != rm) {
            lc->lz.compose(lz);
            rc->lz.compose(lz);
        }
        lz = {};
    }

    void range_update(ll lq, ll rq, lazy x) {
        push();
        if (rq < lm || lq > rm) return;
        if (lq <= lm && rm <= rq) {
            lz.compose(x);
            push();
            return;
        }
        lc->range_update(lq, rq, x);
        rc->range_update(lq, rq, x);
        pull();
    }

    node query(ll lq, ll rq) {
        push();
        if (rq < lm || lq > rm) return neutral;
        if (lq <= lm && rm <= rq) return val;
        return node::comb(lc->query(lq, rq), rc->query(lq, rq));
    }
};

template <bool VALS_EDGES> struct HLD {
	ll N, tim = 0;
	vector<v64> adj;
	v64 parent, sz, head, pos;
    vector<node> vseg;
	std::unique_ptr<tree> seg;
	HLD(vector<v64> adj_, v64 vals)
		: N(adj_.size()), adj(adj_), parent(N, -1), sz(N, 1),
		  head(N),pos(N),vseg(N, {0}){ dfsSz(0); dfsHld(0);
            forn(i,0,N) vseg[i] = {i};
            seg = make_unique<tree>(0, N-1, vseg);
        }
	void dfsSz(ll v) { // get heavy son
		for (ll& u : adj[v]) {
			adj[u].erase(find(adj[u].begin(), adj[u].end(), v));
			parent[u] = v;
			dfsSz(u);
			sz[v] += sz[u];
			if (sz[u] > sz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(ll v) { // "linearizes" the tree
		pos[v] = tim++;
		for (ll u : adj[v]) {
			head[u] = (u == adj[v][0] ? head[v] : u);
			dfsHld(u);
		}
	}
	template <class B> void process(ll u, ll v, B op) {
		for (;; v = parent[head[v]]) {
			if (pos[head[u]] > pos[head[v]]) swap(u, v);
			if (head[u] == head[v]) break;
			op(pos[head[v]], pos[v]);
		}
        if (pos[u] > pos[v]) swap(u, v);
		op(pos[u] + VALS_EDGES, pos[v]);
	}
	void modifyPath(ll u, ll v, ll val) { 
		process(u, v, [&](ll l, ll r) { 
            seg->range_update(l, r, {0, val}); // Modify depending on problem 
        });
	}
	ll queryPath(ll u, ll v) { // Modify depending on problem
		ll res = -INF;
		process(u, v, [&](ll l, ll r) {
				res = max(res, seg->query(l, r).val);
		});
		return res;
	}
	ll querySubtree(ll v) { // modifySubtree is similar
		return seg->query(pos[v] + VALS_EDGES, pos[v] + sz[v] - 1).val;
	}
};

int main(){
    _;
    ll n, q;
    cin >> n >> q;
    vector<v64> g;
    g.resize(n);

    v64 vals(n);
    forn(i,0,n) cin >> vals[i];
    
    forn(i,1,n){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }  

    HLD<false> hld(g, vals);
    
    forn(i,0,n){
        hld.modifyPath(i,i, vals[i]);
    }
    
    while(q--){
        ll t; cin >> t;
        if(t == 1){
            ll s, x;
            cin >> s >> x;
            s--;
            hld.modifyPath(s, s, x);
        }else{
            ll a, b; cin >> a >> b;
            a--; b--;
            cout << hld.queryPath(a,b) << " ";
        }
    }
    cout << ln;
    return 0;
} 
