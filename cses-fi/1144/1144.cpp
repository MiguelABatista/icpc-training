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
    ll val = 0;
    
    static node comb(const node& a, const node& b) {
        return {a.val + b.val};
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
    tree[i] = T::comb(tree[i], v);
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
    v64 vals(n);
    forn(i,0,n){
        cin >> vec[i];
        vals[i] = vec[i];
    }
    vector<query> que(q);
    forn(i,0,q){
        cin >> que[i].c >> que[i].a >> que[i].b;
        vals.push_back(que[i].b);
        if(que[i].c == '?') vals.push_back(que[i].a);
    }   

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    auto compress = [&](ll x){
        return (ll)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
    };

    forn(i,0,n) vec[i] = compress(vec[i]);
    for(auto& [c,a,b] : que){
        if(c == '!') b = compress(b);
        else{
            a = compress(a);
            b = compress(b);
        }
    }

    segtree<node> seg(sz(vals)+1);
    forn(i,0,n) seg.update(vec[i], {1});
    for(auto& [c,a,b] : que){
        if(c == '!'){
            a--;
            ll old = vec[a];
            vec[a] = b;
            seg.update(old,{-1});
            seg.update(b,{1});
        } else{
            cout << seg.query(a,b).val << ln;
        }
    }
    return 0;
}
