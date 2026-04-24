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

// Segment Tree (Range Query + Point Update)
//
//supports point updates and range queries.
//
// complexity: O(log N) per op, O(N)

struct node {
    ll val = 0;
    
    static node comb(const node& a, const node& b) {
        return {max(a.val,b.val)};
    }
};

template<typename T> struct segtree {
  ll n;
  T neutral;
  vector<T> tree;

  segtree(ll _n, T _neutral = T()) {
    n = _n, neutral = _neutral;
    tree.resize(2*n+1, neutral);
  }

  void set_leaves(vector<T> &leaves) {
    copy(leaves.begin(), leaves.end(), tree.begin() + n);

    for (ll i = n - 1; i > 0; i--) tree[i] = T::comb(tree[2 * i], tree[2 * i + 1]);
  }

  void update(ll i, T v) {
    i += n;
    tree[i] = v;
    while (i > 1) {
      i /= 2;
      tree[i] = T::comb(tree[2 * i], tree[2 * i + 1]);
    }
  }

  void update(ll i, ll j, T v){
    assert(i == j);
    update(i,v);
  }

  T query(ll i, ll j) {
    T rl = neutral, rr = neutral;
    for(i += n, j += n; i <= j; i /= 2, j /= 2){
      if((i&1) == 1) rl = T::comb(rl, tree[i++]);
      if((j&1) == 0) rr = T::comb(tree[j--], rr);
    }
    return T::comb(rl, rr);
  }
};

// Heavy Light Decomposition (Path query + Path update)
//
// Decomposes a tree into vertex disjoint heavy paths and light edges such that 
// the path from any leaf to the root contains at most log(n) light edges.
// All values initialized to the segtree default. Root must be 0.
//
// Uses a Lazy Segment Tree  
//
// complexity: O((log N)^2) per op, O(N) build


template <bool VALS_EDGES> struct HLD {
    ll N, tim = 0;
    vector<vll> adj;
    vll parent, siz, head, pos;
    segtree<node> seg;
    HLD(vector<vll> adj_, vll vals)
        : N(sz(adj_)), adj(adj_), parent(N, -1), siz(N, 1),
          head(N),pos(N), seg(N,{-1}){ dfsSz(0); dfsHld(0); 
        }
    void dfsSz(ll v) { // get heavy son
        for (ll& u : adj[v]) {
            adj[u].erase(find(adj[u].begin(), adj[u].end(), v));
            parent[u] = v;
            dfsSz(u);
            siz[v] += siz[u];
            if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
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
            seg.update(l, r, {val}); // Modify depending on problem 
        });
    }
    ll queryPath(ll u, ll v) { // Modify depending on problem
        ll res = -INF;
        process(u, v, [&](ll l, ll r) {
                res = max(res, seg.query(l, r).val);
        });
        return res;
    }
    ll querySubtree(ll v) { // modifySubtree is similar
        return seg.query(pos[v] + VALS_EDGES, pos[v] + siz[v] - 1).val;
    }
};
 
int main(){
    _;
    ll n, q;
    cin >> n >> q;
    vector<vll> g;
    g.resize(n);
 
    vll vals(n);
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
            cout << hld.queryPath(a,b) << (q == 0 ? "" : " ");
        }
    }
    cout << ln;
    return 0;
} 