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
ll mem[100'005];
ll x = 0;

// Segment Tree (Range Query + Point Update)
//
//supports point updates and range queries.
//
// complexity: O(log N) per op, O(N)

struct node {
    ll resp = 0;
    ll tot = 0;
    vector<pll> pref;
    vector<pll> suff;
    node(){}
    node(ll v){
        resp = v==x;
        tot = v;
        pref.push_back({v,1});
        suff.push_back({v,1});
    }

    static node comb(const node& a, const node& b) {
        node n;
        n.resp = a.resp+b.resp;
        
        for(auto [ka, va] : a.suff){
            if(ka%x != 0) continue;
            for(auto [kb, vb] : b.pref){
                if(gcd(kb, ka) == x){
                    n.resp += va*vb;
                }
            }
        }
        n.tot = gcd(a.tot, b.tot);
        
        vll mexido;
        // for(auto [k, v] : a.pref) n.pref[k] += v;
        for(auto [k, v] : a.pref) {
            mem[k] += v;
            mexido.push_back(k);
        }
        // for(auto [k, v] : b.pref) n.pref[gcd(a.tot,k)] += v;
        for(auto [k, v] : b.pref) {
            mem[gcd(a.tot,k)] += v;
            mexido.push_back(gcd(a.tot,k));
        }

        for(ll k : mexido){
            if(mem[k] == 0) continue;
            n.pref.push_back({k,mem[k]});
            mem[k] = 0;   
        }
        mexido.clear();

        // for(auto [k, v] : b.suff) n.suff[k] += v;
        for(auto [k, v] : b.suff){
            mem[k] += v;
            mexido.push_back(k);
        }
        // for(auto [k, v] : a.suff) n.suff[gcd(k, b.tot)] += v;
        for(auto [k, v] : a.suff) {
            mem[gcd(k, b.tot)] += v;
            mexido.push_back(gcd(k, b.tot));
        }

        for(ll k : mexido){
            if(mem[k] == 0) continue;
            n.suff.push_back({k,mem[k]});
            mem[k] = 0;   
        }
        mexido.clear();
        return n;
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
    ll n, q;
    cin >> n >> q >> x;
    segtree<node> seg(n, node());
    vector<node> lef(n);
    forn(i,0,n){
        ll v; cin >> v;
        lef[i] = node(v);
    }
    seg.set_leaves(lef);
    while(q--){
        ll t; cin >> t;
        if(t == 1){
            ll idx, y;
            cin >> idx >> y;
            idx--;
            seg.update(idx, node(y));
        }else{
            ll l, r;
            cin >> l >> r;
            l--;
            r--;

            cout << seg.query(l,r).resp << ln; 
        }
    }
    return 0;
}
