// Template Skeleton
//
// Sets up fast I/O, aliases, and basic macros for contests.

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MAX = 100;

// HLD - vertice
//
// SegTree de soma
// query / update de soma dos vertices
//
// Complexidades:
// build - O(n)
// query_path - O(log^2 (n))
// update_path - O(log^2 (n))
// query_subtree - O(log(n))
// update_subtree - O(log(n))

// Segment Tree with Lazy Propagation (Add/Set)
//
// Supports range add and range set updates with lazy propagation and range queries using a composable lazy state.
//
// complexity: O(log N) per op, O(N)

template<typename T>
struct node {
    ll lm, rm;
    unique_ptr<node> lc, rc;

    static constexpr T neutral = T(); // e.g., 0 for sum, INF for min, etc.
    T val = neutral;
    T lazy_add = T();
    optional<T> lazy_set = nullopt;

    node(ll lm_, ll rm_, const vector<T>& v) : lm(lm_), rm(rm_) {
        if (lm == rm) val = v[lm];
        else {
            ll mid = (lm + rm) / 2;
            lc = make_unique<node>(lm, mid, v);
            rc = make_unique<node>(mid + 1, rm, v);
            pull();
        }
    }

    void push() {
        if (lazy_set.has_value()) {
            val = *lazy_set * (rm - lm + 1);
            if (lm != rm) {
                lc->lazy_set = rc->lazy_set = lazy_set;
                lc->lazy_add = rc->lazy_add = T();
            }
            lazy_set.reset();
        }
        if (lazy_add != T()) {
            val += lazy_add * (rm - lm + 1);
            if (lm != rm) {
                if (lc->lazy_set) *lc->lazy_set += lazy_add;
                else lc->lazy_add += lazy_add;

                if (rc->lazy_set) *rc->lazy_set += lazy_add;
                else rc->lazy_add += lazy_add;
            }
            lazy_add = T();
        }
    }

    void pull() {
        val = comb(lc->val, rc->val);
    }

    static T comb(T a, T b) {
        return a + b; // change for min/max/gcd/etc.
    }

    void range_add(ll lq, ll rq, T x) {
        push();
        if (rq < lm || lq > rm) return;
        if (lq <= lm && rm <= rq) {
            lazy_add += x;
            push();
            return;
        }
        lc->range_add(lq, rq, x);
        rc->range_add(lq, rq, x);
        pull();
    }

    void range_set(ll lq, ll rq, T x) {
        push();
        if (rq < lm || lq > rm) return;
        if (lq <= lm && rm <= rq) {
            lazy_set = x;
            lazy_add = T();
            push();
            return;
        }
        lc->range_set(lq, rq, x);
        rc->range_set(lq, rq, x);
        pull();
    }

    T query(ll lq, ll rq) {
        push();
        if (rq < lm || lq > rm) return neutral;
        if (lq <= lm && rm <= rq) return val;
        return comb(lc->query(lq, rq), rc->query(lq, rq));
    }

    void point_set(ll idx, T x) {
        push();
        if (lm == rm) {
            val = x;
            return;
        }
        if (idx <= lc->rm) lc->point_set(idx, x);
        else rc->point_set(idx, x);
        pull();
    }
};


struct hld {
    ll n, t = 0;
    vector<vector<ll>> g;
    v64 pos, sz, peso, pai, head, base, v, h;
    unique_ptr<node<ll>> seg;

    hld(ll n_): n(n_), g(n_), pos(n_), sz(n_), peso(n_, 0), pai(n_, -1), head(n_), base(n_), v(n_), h(n_){}

	void build_hld(ll k, ll p = -1, ll f = 1) {
		v[pos[k] = t++] = peso[k]; sz[k] = 1;
		for (auto& i : g[k]) if (i != p) {
			pai[i] = k;
			h[i] = (i == g[k][0] ? h[k] : i);
			build_hld(i, k, f); sz[k] += sz[i];

			if (sz[i] > sz[g[k][0]] or g[k][0] == p) swap(i, g[k][0]);
		}
		if (p*f == -1) build_hld(h[k] = k, -1, t = 0);
	}

	void build(ll root = 0) {
		t = 0;
		build_hld(root);
		// seg->build(t, v); ajeitar
	}

	ll query_path(ll a, ll b) {
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return seg->query(pos[b], pos[a]);
		return seg->query(pos[h[a]], pos[a]) + query_path(pai[h[a]], b);
	}
	void update_path(ll a, ll b, ll x) {
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return (void)seg->point_set(pos[b], pos[a], x);
		seg->point_set(pos[h[a]], pos[a], x); update_path(pai[h[a]], b, x);
	}
	ll query_subtree(ll a) {
		return seg->query(pos[a], pos[a]+sz[a]-1);
	}
	void update_subtree(ll a, ll x) {
		seg->point_set(pos[a], pos[a]+sz[a]-1, x);
	}
	ll lca(ll a, ll b) {
		if (pos[a] < pos[b]) swap(a, b);
		return h[a] == h[b] ? b : lca(pai[h[a]], b);
	}
}

int main(){
    _;
    return 0;
}
