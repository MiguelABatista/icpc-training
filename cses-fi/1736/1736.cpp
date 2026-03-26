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

#define debug(u) trace(cout << __LINE__ << ": " #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Segment Tree (Range Query + Range Update)
//
// Tree for range queries with a customizable combine; supports range updates and range queries.
//
// complexity: O(log N) per op, O(N) to build

inline ll esc2(ll n){
    return (n*(n+1))/2;
}

struct Node {
    ll sum;
    ll l, r;
    Node operator*(const Node &o) const { 
        return {sum + o.sum, min(l,o.l), max(r, o.r)}; 
    }
};

struct Update {
    ll q = 0;
    ll y0 = 0;

    Node operator()(const Node &n) const {
        ll sum = n.sum + (n.r-n.l+1)*y0 + q*(esc2(n.r) - esc2(n.l-1)); 
        debug(n.l);
        debug(n.r);
        debug(n.sum);
        debug(sum);
        debug(y0);
        debug(q);
        trace(cout << ln;);
        return {sum, n.l, n.r};
    }

    Update operator+(const Update &o) const {
        return {q+o.q, y0+o.y0};
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

int main() {
    _;
    ll n, q; cin >> n >> q;

    vector<Node> lea(n);
    forn(i,0,n){
        ll x; cin >> x;
        lea[i] = {x,i,i};
    }
    segtree<Node, Update> segtree(n, Node(), Update());
    segtree.set_leaves(lea);

    while (q--){
        ll t; cin >> t;
        ll a, b;
        cin >> a >> b;
        a--, b--;
        
        if(t == 1){
            segtree.update(a,b, {1, -a+1});
        }else{
            debug(1);
            cout << segtree.query(a,b).sum << ln;
        }
    }
    
    return 0;
}
