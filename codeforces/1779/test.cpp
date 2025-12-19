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
    ll n = 5;
    v64 vec = {10,50,30,40,50};
    vector<node> aux(n);

    forn(i,0,n){
        aux[i] = {vec[i], i};
    }

    tree seg(0,n-1, aux);
    cout << seg.query(0,2).val << " " << seg.query(0,2).idx << ln;
    cout << seg.query(0,5).val << " " << seg.query(0,5).idx << ln;
    seg.range_update(0,5, {45});
    cout << seg.query(0,2).val << " " << seg.query(0,2).idx << ln;
    cout << seg.query(0,5).val << " " << seg.query(0,5).idx << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}