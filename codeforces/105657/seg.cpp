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
};

