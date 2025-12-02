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
const ll MAXA = 300'000;

// Segment Tree (Range Query + Point Update)
//
//supports point updates and range queries.
//
// complexity: O(log N) per op, O(N)

struct node {
    ll val = 0;
    
    node(){}
    node(ll a){val = a;}
    static node comb(const node& a, const node& b) {
        return {max(a.val,b.val)};
    }
};

template<typename T> struct segtree {
  ll n;
  T neutral;
  vector<T> tree;

  segtree<T>(ll _n, T _neutral = T()) {
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

int main(){
    _;
    ll n, k; 
    cin >> n >> k;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    segtree seg(MAXA+1, (node){0});

    forn(i,0,n){
        ll a = vec[i];

        ll l = max(0ll, a-k);
        ll r = min(MAXA, a+k);
        ll ans = seg.query(l, r).val + 1;

        seg.update(a, {ans});
    }

    cout << seg.query(0, MAXA).val << ln;
    return 0;
}

