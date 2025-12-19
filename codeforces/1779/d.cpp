#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Segment Tree (Range Query + Range Update)
//
// Balanced binary tree for range queries with a customizable combine; supports point updates and range queries.
//
// complexity: O(log N) per op, O(N)

struct lazy {
    optional<ll> set;
    
    void compose(const lazy& o) {
        if (o.set.has_value()) {
            if(set.has_value()){
                set = min(set, o.set);
            }else{
                set = o.set;
            }
        }
    }
};

struct node {
    ll val = 0; 
    ll idx = 0;
    
    static node comb(const node& a, const node& b) {
        node n;
        if(a.val > b.val){
            n.val = a.val;
            n.idx = a.idx;
        }else{
            n.val = b.val;
            n.idx = b.idx;
        }
        return n;
    }

    void resolve(const lazy& lz, ll l, ll r) {
        if (lz.set.has_value()) val = min(val, *lz.set);
    }
};

const node neutral = {-INF};

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


void solve(){
    ll n; cin >> n;
    v64 a(n), b(n);
    forn(i,0,n) cin >> a[i];
    forn(i,0,n) cin >> b[i];

    set<p64> s;
    forn(i,0,n) s.insert({b[i], i});
    
    ll m; cin >> m;
    v64 razors(m);
    forn(i,0,m) cin >> razors[i];
    
    forn(i,0,n){
        if(a[i] < b[i]){
            cout << "NO" << ln;
            return;
        }
    }
    sort(razors.begin(), razors.end());

    vector<node> auxa(n), auxb(n);
    forn(i,0,n){
        auxa[i] = {a[i], i};
        auxb[i] = {b[i], i};
    }

    tree sega(0, n-1, auxa);
    tree segb(0, n-1, auxb);

    priority_queue<pair<p64, p64>> pq;
    node aaaaa = segb.query(0,n-1);

    pq.push({{aaaaa.val, aaaaa.idx}, {0, n-1}});

    forn(i,0,n){
        auto [p1, p2] = pq.top();
        pq.pop();

        auto [val, idx] = p1;
        auto [l, r] = p2;

        trace(
            cout << sz(pq) << ln;
            cout << val << " " << idx << " " << l << " " << r << ln;
        );

        debug(sega.query(idx,idx).val);

        if(sega.query(idx,idx).val == val){
            if(l <= idx-1){
                node aux = segb.query(l,idx-1);
                pq.push({{aux.val, aux.idx},{l, idx-1}});
            }

            if(idx+1 <= r){
                node aux = segb.query(idx+1, r);
                pq.push({{aux.val, aux.idx},{idx+1, r}});
            }

            continue;
        };

        debug(1);
        while(!razors.empty() && razors.back() > val) razors.pop_back();
        if(razors.empty() || razors.back() < val){
            cout << "No" << ln;
            return;
        }
        razors.pop_back();

        trace(
            cout << l << " " << r << " " << val << ln;
        );

        debug(val);
        sega.range_update(l, r, {val});

        if(l <= idx-1){
            node aux = segb.query(l,idx-1);
            pq.push({{aux.val, aux.idx},{l, idx-1}});
        }
        
        if(idx+1 <= r){
            node aux = segb.query(idx+1, r);
            pq.push({{aux.val, aux.idx},{idx+1, r}});
        }   
    }
    cout << "YES" << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}