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

struct query{
    char c;
    ll a, b;
};

// Segment Tree (Range Query + Point Update)
//
//supports point updates and range queries.
//
// complexity: O(log N) per op, O(N)

struct node {
    ll sum = 0;
    ll best = 0;

    static node comb(const node& a, const node& b) {
        ll ns = a.sum + b.sum;
        ll nb = max(a.best, a.sum+b.best);
        return {ns, nb};
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

int main() {
    _;
    ll n, q; cin >> n >> q;
    vector<node> vec(n);

    forn(i,0,n){
        ll x; cin >> x;
        vec[i] = {x, max(x,0ll)};
    }

    segtree seg(n, node());
    seg.set_leaves(vec);

    while(q--){
        ll t;
        cin >> t;
        if(t == 1){
            ll k, u; 
            cin >> k >> u;
            k--;
            seg.update(k,{u, max(u,0ll)});
        }else{
            ll a, b;
            cin >> a >> b;
            a--; b--;
            cout << seg.query(a,b).best << ln;
        }
    }
    return 0;
}
