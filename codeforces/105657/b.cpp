#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void) 0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

struct lazy {
    optional<ll> set;

    void compose(const lazy& o) {
        if (o.set.has_value()) {
            set = o.set;
        }
    }
};

struct node {
    ll val = 0;
    
    static node comb(const node& a, const node& b) {
        return {a.val + b.val};
    }

    void resolve(const lazy& lz, ll l, ll r) {
        if (lz.set.has_value()) val = *lz.set * (r - l + 1);
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
            lc = make_unique<tree>(lm,m, v);
            rc = make_unique<tree>(m+1, rm, v);
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

    ll zero_idx(ll lq, ll rq) {
        push();
        if(lm == rm) return (val.val == 0 ? lm : INF);

        if (rq < lm || lq > rm) return INF;
        if (lq <= lm && rm <= rq) {
            if (val.val == rm-lm-1) return INF;
        }

        ll left_zero = lc->zero_idx(lq, rq);
        if(left_zero != INF) return left_zero;
        return rc->zero_idx(lq, rq);
    }

    void print(){
        push();
        if(lm == rm){
            cout << val.val << " ";
            return;
        }
        lc->print();
        rc->print();
    }
};

int main() {
    _;
    ll n, q; cin >> n >> q;
    
    vector<vector<node>> vec(63, vector<node>(n));

    forn(i,0,n){
        ll x; cin >> x;
        ll pot2 = 1;
        forn(j,0,63){
            vec[j][i] = {!!(pot2&x)};
            pot2 <<= 1; 
        }
    }

    
    vector<tree> segs;

    forn(i,0,63){
        segs.push_back(tree(0,n-1,vec[i]));
    }
    

    while(q--){
        // forn(i,0,5){
        //     cout << i << ": ";
        //     segs[i].print();
        //     cout << ln;
        // }
    
        ll t; cin >> t;
        if(t == 1){
            ll l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            ll pot2 = 1;
            forn(i,0,63){
                ll bit = !!(pot2&x);
                if(bit == 0){
                    segs[i].range_update(l, r, {0});
                }
                pot2 <<= 1; 
            }
        }

        if(t == 2){
            ll s, x;
            cin >> s >> x;
            s--;
            ll pot2 = 1;
            forn(i,0,63){
                ll bit = !!(pot2&x);
                segs[i].range_update(s, s, {bit});
                pot2 <<= 1; 
            }
        }

        if(t == 3){
            ll l, r;
            cin >> l >> r;
            l--; r--;
            ll pot2 = 1ll<<62;
            bool usado = false;
            ll idx_usado = -1; 
            ll resp = 0;

            for(ll i = 62; i >= 0; i--){
                ll amount = segs[i].query(l, r).val;

                if(usado){
                    ll aux = segs[i].query(idx_usado, idx_usado).val;
                    if(aux == 0) amount++;
                }

                // if(i < 5){
                //     debug(i);
                //     debug(resp);
                //     debug(pot2);
                //     debug(usado);
                //     cout << ln;
                // }


                if(amount == r-l+1){
                    resp += pot2;
                }
                
                if(amount == r-l && !usado){
                    resp += pot2;
                    usado = true;
                    idx_usado = segs[i].zero_idx(l, r);
                }

                pot2 >>= 1; 
            }
            cout << resp << ln;
        }
    }
    return 0;
}