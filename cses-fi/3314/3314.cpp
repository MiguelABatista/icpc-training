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

// Segment Tree (Range Query + Point Update)
//
//supports point updates and range queries.
//
// complexity: O(log N) per op, O(N)

struct node {
    ll val = 0;
    ll idx = -1;
    static node comb(const node& a, const node& b) {
        if(a.val >= b.val) return a;
        return b;
    }
};

template<typename T> struct segtree {
  ll n;
  T neutral;
  vector<T> tree;

  segtree(ll _n, T _neutral = T()) {
    n = _n, neutral = _neutral;
    tree.resize(2*n+1, neutral);
  }

  void set_leaves(vector<T> &leaves) {
    copy(leaves.begin(), leaves.end(), tree.begin() + n);

    for (ll i = n - 1; i > 0; i--) tree[i] = T::comb(tree[2 * i], tree[2 * i + 1]);
  }

  void update(ll i, T v) {
    i += n;
    tree[i] = v;
    while (i > 1) {
      i /= 2;
      tree[i] = T::comb(tree[2 * i], tree[2 * i + 1]);
    }
  }

  T query(ll i, ll j) {
    T rl = neutral, rr = neutral;
    for(i += n, j += n; i <= j; i /= 2, j /= 2){
      if((i&1) == 1) rl = T::comb(rl, tree[i++]);
      if((j&1) == 0) rr = T::comb(tree[j--], rr);
    }
    return T::comb(rl, rr);
  }
};

v64 vec;

p64 dnc(ll l, ll r, segtree<node>& seg){
    if(l >= r) return {1, vec[l]};

    auto no = seg.query(l,r);
    ll val = no.val;
    ll idx = no.idx;

    auto p1 = dnc(l, idx-1, seg);
    auto p2 = dnc(idx+1, r, seg);

    ll val1 = p1.first + !(val == p1.second);
    ll val2 = p2.first + !(val == p2.second);
    return {max(val1, val2), vec[idx]};
}

int main() {
    _;
    ll n; cin >> n;
    vec.resize(n);
    v64 dp(n);
    forn(i,0,n) cin >> vec[i];
    
    segtree<node> seg(n);
    vector<node> aux(n);
    forn(i,0,n) aux[i] = {vec[i], i};
    seg.set_leaves(aux);

    cout << dnc(0,n-1, seg).first << ln;
}
