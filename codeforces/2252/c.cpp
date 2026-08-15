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
    ll min = INF, minidx = -1;

    Node operator*(const Node &o) const { 
        if(min < o.min) return {min, minidx};
        else return {o.min, o.minidx};
    }
};

struct Update {
    ll add = 0;

    Node operator()(const Node &n) const {
        return {n.min+add, n.minidx};
    }

    Update operator+(const Update &o) const {
        return {add + o.add};
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


// Fenwick Tree (Binary Indexed Tree)
//
// Supports point updates and prefix/range sum queries in logarithmic time using a 1-indexed BIT.
//
// complexity: O(log N) per op, O(N)

struct Bit {
    ll n;
    vll bit;
    Bit(ll _n = 0) : n(_n), bit(n + 1) {}
    void update(ll i, ll x) { // soma x na posicao i
        for (i++; i <= n; i += i & -i) bit[i] += x;
    }
    ll pref(ll i) { // soma [0, i]
        ll ret = 0;
        for (i++; i; i -= i & -i) ret += bit[i];
        return ret;
    }
    ll query(ll l, ll r) {  // soma [l, r]
        return pref(r) - pref(l - 1); 
    }
};


void solve(){
    ll n, m; cin >> n >> m;
    vector<vll> mat(n, vll(m));
    
    vll est(n); forn(i,0,n) cin >> est[i];

    vector<tuple<ll,ll,ll>> vec;
    
    forn(i,0,n) forn(j,0,m){
        cin >> mat[i][j];
        vec.push_back({-mat[i][j], -i, j});
    }
    sort(vec.begin(), vec.end());

    segtree<Node, Update> seg(n);
    Bit bit(n);
    vector<Node> lfs(n);
    forn(i,0,n) lfs[i] = {est[i], i};
    seg.set_leaves(lfs);

    ll resp = INF;
    for(auto [v, r, c] : vec){
        r *= -1;
        seg.update(0,r, {v});
        bit.update(r, 1);
        while(true){
            auto no = seg.query(0,n-1);
            if(no.min > 0) break;
            resp = min(resp, bit.query(no.minidx,n-1));
            seg.update(no.minidx, no.minidx, {INF});
        }
    }

    debugv(used);
    debugv(used);
    cout << min(resp, m) << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
