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

struct node {
    ll pref, suf, sum, best;

    static node comb(const node& a, const node& b) {
        return {
            max(a.pref, a.sum + b.pref),
            max(b.suf, a.suf + b.sum),
            a.sum+b.sum,
            max({a.best, b.best, a.suf + b.pref})
        };
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

  ll find(ll rr, ll x) {
    ll l = 0, r = rr, ans = rr+1;

    while (l <= r) {
        ll mid = (l+r)/ 2;
        if (query(l, r).best > x) {
            l = mid + 1;
        } else {
            r = mid - 1;
            ans = mid;
        }
    }
    return ans;
  }
};

void solve() {
    ll n, k; cin >> n >> k;
    v64 v(n);
    forn(i, 0, n) cin >> v[i];
    segtree<node> seg(n);
    vector<node> vetor(n);
    forn(i,0, n) vetor[i] = {max(v[i], 0ll), max(v[i], 0ll), v[i], max(v[i], 0ll)};
    seg.set_leaves(vetor);
    ll ans = 0;
    
    forn(i, 0, n) {
        debug(seg.find(i, k));
        debug(seg.find(i, k-1));

        ans += i - seg.find(i, k) + 1;
        ans -= i - seg.find(i, k-1) + 1;
    }

    cout << ans << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while (t--) solve();
    return 0;
}