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

// Segment Tree (Range Query + Range Update)
//
// Tree for range queries with a customizable combine; supports range updates and range queries.
//
// complexity: O(log N) per op, O(N) to build

struct Node {
    ll currsum = 0;
    ll tot = 0;
    Node operator*(const Node &o) const {
         return {currsum + o.currsum,  tot + o.tot}; }
};

struct Update {
    ll state = 0;
    ll val = -1;
    Node operator()(const Node &n) const {
        if(val != -1) return {0, val};
        if(state == 0) return n;
        return {n.tot - n.currsum, n.tot};
    }

    Update operator+(const Update &o) const {
        return {state^o.state, val};
    }
};

template<typename T, typename U> struct segtree {
  ll s, h;

  T id;
  vector<T> val;

  U noop;
  vector<bool> dirty;
  vector<U> prop;

  segtree(ll ts, T tid = T(), U tnoop = U()) {
    id = tid, noop = tnoop;
    for (s = 1, h = 1; s < ts; ) s *= 2, h++;

    val.assign(2*s, id);
    dirty.assign(2*s, false);
    prop.assign(2*s, noop);
  }

  void set_leaves(vector<T> &lvs) {
    copy(lvs.begin(), lvs.end(), val.begin() + s);

    for (ll i = s - 1; i > 0; i--) val[i] = val[2 * i] * val[2 * i + 1];
    dirty.assign(2*s, false);
    prop.assign(2*s, noop);
  }

  void apply(ll i, U &upd) {
    val[i] = upd(val[i]);
    if(i < s) {
      prop[i] = prop[i] + upd;
      dirty[i] = true;
    }
  }

  void pull(ll i) {
    for (ll l = i/2; l; l /= 2) {
      T comb = val[2*l] * val[2*l+1];
      val[l] = prop[l](comb);
    }
  }

  void push(ll i) {
    for (ll th = h; th > 0; th--) {
      ll l = i >> th;

      if (dirty[l]) {
        apply(2*l, prop[l]);
        apply(2*l+1, prop[l]);

        prop[l] = noop;
        dirty[l] = false;
      }
    }
  }

  void update(ll i, ll j, U upd) {
    i += s, j += s;
    push(i), push(j);

    for (ll l = i, r = j; l <= r; l /= 2, r /= 2) {
      if((l&1) == 1) apply(l++, upd);
      if((r&1) == 0) apply(r--, upd);
    }

    pull(i), pull(j);
  }

  T query(ll i, ll j){
    i += s, j += s;
    push(i), push(j);

    T rl = id, rr = id;
    for(; i <= j; i /= 2, j /= 2){
      if((i&1) == 1) rl = rl * val[i++];
      if((j&1) == 0) rr = val[j--] * rr;
    }
    return rl * rr;
  }
};


// Heavy Light Decomposition (Path query + Path update)
//
// Decomposes a tree into vertex disjoint heavy paths and light edges such that 
// the path from any leaf to the root contains at most log(n) light edges.
// All values initialized to the segtree default. Root must be 0.
//
// head[u]: Highest node (closest to root) of the heavy path containing u.
// pos[u]: Position of node u in the Segment Tree array (DFS order).
// Uses a Lazy Segment Tree  
//
// complexity: O((log N)^2) per op, O(N) build

template <bool VALS_EDGES> struct HLD {
    ll N, tim = 0;
    vector<vll> adj;
    vll parent, siz, head, pos;
    std::unique_ptr<segtree<Node, Update>> seg;
    HLD(vector<vll> adj_)
        : N(sz(adj_)), adj(adj_), parent(N, -1), siz(N, 1),
          head(N),pos(N){ dfsSz(0); dfsHld(0);
            seg = make_unique<segtree<Node, Update>>(N);
        }
    void set_leaves(const vector<Node>& lvs) { // lvs[i] is the weight of i -> parent[i]
        vector<Node> leaves(N); 
        forn(i, 0, N) leaves[pos[i]] = lvs[i]; 
        seg->set_leaves(leaves);
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
    void modifyPath(ll u, ll v, Update val) { 
        process(u, v, [&](ll l, ll r) { 
            seg->update(l, r, val); // Modify depending on problem 
        });
    }
    // ll queryPath(ll u, ll v) { // Modify depending on problem
    //     ll res = -INF;
    //     process(u, v, [&](ll l, ll r) {
    //             res = max(res, seg->query(l, r).val);
    //     });
    //     return res;
    // }
    ll querySubtree(ll v) { // modifySubtree is similar
        return seg->query(pos[v] + VALS_EDGES, pos[v] + siz[v] - 1).currsum;
    }
};

int main() {
    _;

    ll n, q; cin >> n >> q;
    vector<vector<pll>> gg(n);
    vector<vll> g(n);

    forn(i,0,n-1){
        ll a, b, w; cin >> a >> b >> w;
        a--,b--;
        gg[a].push_back({b,w});
        gg[b].push_back({a,w});
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<Node> vec(n);
    vector<ll> pai(n);
    
    function<void (ll, ll)> dfs = [&](ll u, ll p){
        for(auto [v,w]: gg[u]) if(v != p){
            vec[v] = {0,w};
            dfs(v,u);
        }
    };

    dfs(0, -1);
    HLD<true> hld(g);
    hld.set_leaves(vec);
    // forn(i,0,n) if(pai[i] != -1) hld.modifyPath(i, pai[i], {0, vec[i]});

    while(q--){
        ll a, b; cin >> a >> b;
        a--, b--;
        hld.modifyPath(a,b, {1, -1});
        debug(1);
        cout << hld.querySubtree(0) << ln;
    }

    return 0;
}