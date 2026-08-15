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
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Segment Tree (Range Query + Point Update)
//
//supports point updates and range queries.
//
// complexity: O(log N) per op, O(N)

struct node {
    ll val = INF;
    
    static node comb(const node& a, const node& b) {
        return {min(a.val,b.val)};
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


void solve(){
    ll n; cin >> n;
    string s; cin >> s;
    vll next(n);

    next[n-1] = n;
    for(ll i = n-2; i >= 0; i--){
        if(s[i] == '.'){
            next[i] = -1;
            continue;
        } 
        if(s[i+1] == '.'){
            next[i] = i;
            continue;
        }
        next[i] = next[i+1];
    }

    segtree seg(n,node());

    seg.update(n-1, {0});

    for(ll i = n-2; i >= 0; i--){
        if(s[i] == '.') continue;
        if(next[i] == n){
            seg.update(i, {0});
            continue;
        }

        ll pulo = next[i] - i;
        ll fim = next[i]+1+pulo;
        if(fim >= n-1) fim = n-1; 

        ll ans = seg.query(next[i]+1, fim).val + 1;
        if(ans > INF/2) ans = INF;
        seg.update(i, {ans});
    }

    ll ans = seg.query(0,0).val;
    if(ans == INF) ans = -1;
    cout << ans  << ln;
    
    trace(cout <<"d = ";forn(i,0,n) cout << i%10;; cout << ln;)
    debug(s);
    debugv(next);
    trace(cout << "----------------------------\n\n";)
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
