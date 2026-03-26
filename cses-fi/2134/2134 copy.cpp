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


// Heavy Light Decomposition (Path query + Path update)
//
// Decomposes a tree into vertex disjoint heavy paths and light edges such that 
// the path from any leaf to the root contains at most log(n) light edges.
// All values initialized to the segtree default. Root must be 0.
//
// Uses a Lazy Segment Tree  
//
// complexity: O((log N)^2) per op, O(N) build

// Segment Tree (Range Query + Range Update)
//
// Tree for range queries with a customizable combine; supports range updates and range queries.
//
// complexity: O(log N) per op, O(N) to build

struct Node {
    ll val;
    Node operator*(const Node &o) const { return {max(val, o.val)}; }
};

struct Update {
    optional<ll> set;

    Node operator()(const Node &n) const {
        ll res = set.has_value() ? *set : n.val;
        return {res};
    }

    Update operator+(const Update &o) const {
        Update res = *this;
        if (o.set.has_value()) {
            res.set = o.set;
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

    explicit segtree(ll ts, T tid = T(), U tnoop = U()) {
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

template <bool VALS_EDGES> struct HLD {
    ll N, tim = 0;
    vector<v64> adj;
    v64 parent, siz, head, pos;
    vector<Node> vseg;
    std::unique_ptr<segtree<Node, Update>> seg;
    HLD(vector<v64> adj_, v64 vals)
        : N(sz(adj_)), adj(adj_), parent(N, -1), siz(N, 1),
          head(N),pos(N),vseg(N, {0}){ dfsSz(0); dfsHld(0);
            seg = make_unique<segtree<Node, Update>>(N);
            seg->set_leaves(vseg);
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
            seg->update(l, r, {val}); // Modify depending on problem 
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
        return seg->query(pos[v] + VALS_EDGES, pos[v] + siz[v] - 1).val;
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