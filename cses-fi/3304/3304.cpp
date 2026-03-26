#include <bits/stdc++.h>
using namespace std;

typedef int ll;
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

// const ll INF = 0x3f3f3f3f3f3f3f3fll;


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
    tree[i] = node::comb(tree[i], v);
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
    vector<tuple<ll,ll>> querries(q);

    forn(i,0,n){
        cin >> vec[i];
    }

    forn(i,0,q){
        ll a, b;
        cin >> a >> b;
        a--, b--;
        querries[i] = {a,b};
    }


    vector<p64> st;
    v64 aux(n);
    forn(i,0,n){
        while (!st.empty() && st.back().first < vec[i]) st.pop_back();
        if(st.empty()) aux[i] = -1;
        else aux[i] = st.back().second;
        st.push_back({vec[i],i});
    }

    debugv(aux);
    vector<vector<tuple<ll,ll>>> as(n);
    vector<vector<tuple<ll,ll>>> bs(n);
    
    forn(i,0,q){
        auto& [a,b]=  querries[i];
        if(a > 0) as[a-1].push_back({a,i});
        bs[b].push_back({a,i});
    }

    v64 resp(q);
    segtree seg(n+1, node());

    forn(i,0,n){
        seg.update(aux[i]+1, {1});
        debug(i);
        for(auto [a,t] : as[i]){
            debug('a');
            debug(a);
            debug(t);
            debug(seg.query(0,a).val);
            resp[t] -= seg.query(0,a).val;
        }
        for(auto [a,t] : bs[i]){
            debug('b');
            debug(a);
            debug(t);
            debug(seg.query(0,a).val);
            resp[t] += seg.query(0,a).val;
        }
    }

    forn(i,0,q) cout << resp[i] << ln;
    return 0;
}
