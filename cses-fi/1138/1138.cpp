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
    ll sum, cnt;
    Node operator*(const Node &o) const { return {sum + o.sum, cnt + o.cnt}; }
};

struct Update {
    ll add = 0;
    optional<ll> set;

    Node operator()(const Node &n) const {
        ll res = set.has_value() ? *set * n.cnt : n.sum;
        return {res + add * n.cnt, n.cnt};
    }

    Update operator+(const Update &o) const {
        Update res = *this;
        if (o.set.has_value()) {
            res.set = o.set;
            res.add = 0;
        }
        if (o.add != 0) {
            if (res.set.has_value()) *res.set += o.add;
            else res.add += o.add;
        }
        return res;
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
    void set_leaves(const vector<Node>& lvs) {
        // if VALS_EDGES lvs[i] is the weight of i -> parent[i]
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
    void modifyPath(ll u, ll v, Update upd) { 
        process(u, v, [&](ll l, ll r) { 
            seg->update(l, r, upd); 
        });
    }
    Node queryPath(ll u, ll v) { 
        Node res = Node();
        // Non-commutative ops require exact merge order.
        process(u, v, [&](ll l, ll r) {
            res = res*seg->query(l, r);
        });
        return res;
    }
    Node querySubtree(ll v) { 
        return seg->query(pos[v] + VALS_EDGES, pos[v] + siz[v] - 1);
    }
    void modifySubtree(ll v, Update upd) {
        seg->update(pos[v] + VALS_EDGES, pos[v] + siz[v] - 1, upd);
    }
};

int main() {
    _;
    ll n, q; cin >> n >> q;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];

    vector<vll> g(n);
    forn(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<Node> lvs(n);
    forn(i,0,n) lvs[i] = {vec[i], 1};
    
    HLD<false> hld(g);
    hld.set_leaves(lvs);
    while(q--){
        ll t; cin >> t;
        if(t == 2){
            ll v; cin >> v;
            v--;
            cout << hld.queryPath(v, 0).sum << ln;
        }else{
            ll v, x;
            cin >> v >> x;
            v--;
            hld.modifyPath(v,v,{0,x});
        }
    }

    return 0;
}
