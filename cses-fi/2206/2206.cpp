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
    ll val = INF;
    
    static node comb(const node& a, const node& b) {
        return {min(a.val, b.val)};
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
    v64 vec(n);
    vector<node> vl(n), vr(n);

    forn(i,0,n){
        cin >> vec[i];
        vl[i] = {vec[i] - i};
        vr[i] = {vec[i] + i};
    }
    segtree segl(n, node()); // pi - xi
    segl.set_leaves(vl);
    segtree segr(n, node()); // pi + xi
    segr.set_leaves(vr);
    

    forn(i,0,q){
        ll t;
        cin >> t;
        if(t == 1){
            ll k, x;
            cin >> k >> x;
            k--;
            vec[k] = x;
            segl.update(k, {x-k});
            segr.update(k, {x+k});
        }else{
            ll k; cin >> k;
            k--;
            ll bl = k + segl.query(0,k).val;
            ll br = segr.query(k,n-1).val - k;
            cout << min(bl,br) << ln;
        }   
    }


    return 0;
}
