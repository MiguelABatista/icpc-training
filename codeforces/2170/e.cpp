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
const ll MOD = 998244353;

// Segment Tree (Range Query + Point Update)
//
//supports point updates and range queries.
//
// complexity: O(log N) per op, O(N)

struct node {
    ll val = 0;
    
    static node comb(const node& a, const node& b) {
        ll s = a.val + b.val;
        return {(s >= MOD ? s - MOD : s)};
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

void solve(){
    ll n, m; cin >> n >> m;
    v64 dp(n);
    
    segtree<node> seg(n,{0});

    vector<p64> q(m);
    v64 r_to_l(n,-1);

    forn(i,0,m){
        cin >> q[i].first >> q[i].second;
        q[i].first--;
        q[i].second--;
    }

    forn(i,0,m){
        r_to_l[q[i].second] = max(r_to_l[q[i].second], q[i].first);
    }

    ll maxl = -1;
    v64 maxlv(n);
    maxlv[0] = -1;
    dp[0] = 1;
    seg.update(0, {dp[0]});
    forn(i,1,n){
        maxl = max(maxl, r_to_l[i]);
        maxlv[i] = maxl;
        if(r_to_l[i] == -1){
            dp[i] = (2*dp[i-1])%MOD;
        }else{
            dp[i] = seg.query(maxl, i).val;
        }
        seg.update(i, {dp[i]});
    }

    debugv(maxlv);
    debugv(dp);
    cout << (2*dp[n-1])%MOD << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}