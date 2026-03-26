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

// DSU with Rollback (Persistent/Undoable Union-Find)
//
// Allows merging sets and undoing operations to a previous state
// using a stack of modifications. No Path Compression to keep
// tree structure reversible.
//
// complexity: O(log N) per find/unite, O(1) per checkpoint/rollback

struct dsu_rb {
    v64 id, len;
    ll allbip = true;
    stack<pair<ll&, ll>> st;
    dsu_rb(ll n) : id(n), len(n, 1) { 
        iota(id.begin(), id.end(), 0); 
    }
    void save(ll &x) {  st.emplace(x, x);}
    ll time() { return sz(st); }
    void rollback(ll t) {
        while(sz(st) > t) {
            auto [end, val] = st.top(); st.pop();
            end = val;
        }
    }
    ll find(ll a) { return a == id[a] ? a : find(id[a]); }
    bool unite(ll a, ll b) {
        a = find(a), b = find(b);
        if (a == b) return false;        
        if (len[a] < len[b]) swap(a, b);
		save(len[a]);
        save(id[b]);
        len[a] += len[b], id[b] = a;
		return true;
    }
};

struct Edge {ll a, b, w; };
struct Node {
	Edge key;
	Node *l, *r;
	ll delta;
	void prop() {
		key.w += delta;
		if (l) l->delta += delta;
		if (r) r->delta += delta;
		delta = 0;
	}
	Edge top() { prop(); return key; }
};
Node *merge(Node *a, Node *b) {
	if (!a || !b) return a ?: b;
	a->prop(), b->prop();
	if (a->key.w > b->key.w) swap(a, b);
	swap(a->l, (a->r = merge(b, a->r)));
	return a;
}
void pop(Node*& a) { a->prop(); a = merge(a->l, a->r); }

pair<ll, v64> dmst(ll n, ll src, vector<Edge>& g) {
	dsu_rb uf(n);
	vector<Node*> heap(n);
	for (Edge e : g) heap[e.b] = merge(heap[e.b], new Node{e});
	ll res = 0;
	v64 seen(n, -1), path(n), par(n);
	seen[src] = src;
	vector<Edge> Q(n), in(n, {-1,-1}), comp;
	deque<tuple<ll, ll, vector<Edge>>> cycs;
	forn(s,0,n) {
		ll u = s, qi = 0, w;
		while (seen[u] < 0) {
			if (!heap[u]) return {-1,{}};
			Edge e = heap[u]->top();
			heap[u]->delta -= e.w, pop(heap[u]);
			Q[qi] = e, path[qi++] = u, seen[u] = s;
			res += e.w, u = uf.find(e.a);
			if (seen[u] == s) { /// found cycle, contract
				Node* cyc = 0;
				ll end = qi, time = uf.time();
				do cyc = merge(cyc, heap[w = path[--qi]]);
				while (uf.unite(u, w));
				u = uf.find(u), heap[u] = cyc, seen[u] = -1;
				cycs.push_front({u, time, {&Q[qi], &Q[end]}});
			}
		}
		forn(i,0,qi) in[uf.find(Q[i].b)] = Q[i];
	}

	for (auto& [u,t,com] : cycs) { // restore sol (optional)
		uf.rollback(t);
		Edge inEdge = in[u];
		for (auto& e : com) in[uf.find(e.b)] = e;
		in[uf.find(inEdge.b)] = inEdge;
	}
	forn(i,0,n) par[i] = in[i].a;
	return {res, par};
}

int main() {
    _;
	ll n, m, s;
	cin >> n >> m >> s;
	vector<Edge> g(m);
	forn(i,0,m){
		cin >> g[i].a >> g[i].b >> g[i].w;
	}
	auto [cost, parent] = dmst(n, s, g);
	cout << cost << ln;
	forn(i,0,sz(parent)){
		cout << ((parent[i] == -1) ? s : parent[i]) << " \n"[i==sz(parent)-1];
	}
    return 0;
}
 