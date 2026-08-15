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

// Segment Tree Over Time (Dynamic Connectivity Skeleton)
//
// Stores edge activation intervals in a segment tree over time to enable offline dynamic connectivity with rollback DSU.

struct Node{
    ll a, b; // aresta a,b
};

struct time_node {
    ll lm, rm;
    unique_ptr<time_node> lc, rc;

    vector<Node> op;

    time_node(ll lm_, ll rm_){
        lm = lm_;
        rm = rm_;
        if (lm != rm) {
            ll mid = (lm + rm) / 2;
            lc = make_unique<time_node>(lm, mid);
            rc = make_unique<time_node>(mid + 1, rm);
        }
    }

    void add_query(ll lq, ll rq, Node x) {
        if (rq < lm || lq > rm) return;
        if (lq <= lm && rm <= rq) {
            op.push_back(x);
            return;
        }
        lc->add_query(lq, rq, x);
        rc->add_query(lq, rq, x);
    }
};

// DSU with Rollback (Persistent/Undoable Union-Find)
//
// Allows merging sets and undoing operations to a previous state
// using a stack of modifications. No Path Compression to keep
// tree structure reversible.
//
// complexity: O(log N) per find/unite, O(1) per checkpoint/rollback

struct dsu_rb {
    vll id, len;
    ll num_comp;
    stack<pair<ll&, ll>> st;

    dsu_rb(ll n) : id(n), len(n, 1) { 
        iota(id.begin(), id.end(), 0); 
        num_comp = n;
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
        save(num_comp);
        len[a] += len[b], id[b] = a;
        num_comp--;
		return true;
    }
};

int main() {
    _;
    ll n, m, q; cin >> n >> m >> q;

    vector<tuple<ll,ll,ll,ll>> arestas;
    // {a,b,nasce,morre} 
    
    map<pll, ll> nasceu;

    forn(i,0,m){
        ll a, b; cin >> a >> b;
        a--, b--;
        nasceu[{min(a,b), max(a,b)}] = 0;
    }
    
    forn(t,1,q+1){
        ll c, a, b; cin >> c >> a >> b;
        a--, b--;
        if(a == b) continue;
        if(c == 1) nasceu[{min(a,b), max(a,b)}] = t;
        if(c == 2) {
            arestas.push_back({min(a,b), max(a,b), nasceu[{min(a,b), max(a,b)}], t-1});
            nasceu.erase({min(a,b), max(a,b)});
        }
    }
    for(auto [p, v] : nasceu){
        auto [a,b] = p;
        arestas.push_back({a,b, v, q+1});
    }

    unique_ptr<time_node> root = make_unique<time_node>(0, q+1);
    dsu_rb dsu(n);

    for(auto [a,b, tin, tout] : arestas){
        root->add_query(tin,tout, {a,b});
    }

    vll ans(q+2);

    function<void (time_node*)> dfs = [&](time_node *curr){
        ll voltar = dsu.time();
        for(auto [a,b] : curr->op) dsu.unite(a,b);
        if(curr->lm == curr->rm){
            ans[curr->lm] = dsu.num_comp;
        }else{
            dfs(curr->lc.get());
            dfs(curr->rc.get());
        }  
        dsu.rollback(voltar);
    };
 
    dfs(root.get());

    forn(i,0,q+1) cout << ans[i] << " \n"[i==q];
    return 0;
}
