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

struct Ven{
    set<pll> s = {INF, INF};
    ll offset = 0;

    void insert(ll x, ll idx){
        s.insert({x-offset, idx});
    }
    void add_all(ll x){
        offset += x;
    }
    ll lb(ll x){
        x -= offset;
        return s.lower_bound({x,-1})->second;
    }
    void dbg(){
        debug(offset);
        debugv(s);
    }
};

void solve(){
    ll n; cin >> n;
    string s; cin >> s;
    vector<pll> veccc;
    
    ll curr = 1;
    forn(i,1,n){
        if(s[i] == s[i-1]){
            curr++;
            continue;
        }else{
            veccc.push_back({curr, (ll)(s[i]=='.')});
            curr = 1;
        }
    }

    vector<pll> vec;
    for(ll i = 0; i < sz(veccc); i += 2) vec.push_back({veccc[i].first, veccc[i+1].first});
    debugm(vec);
    n = sz(vec);

    Ven ven;
    segtree seg(n, node());

    for(ll i = n-1; i >= 0; i--){
        ven.insert(0ll, i);
        ven.add_all(vec[i].first + vec[i].second);
        
        // nao consegue pular, resp = INF
        if(vec[i].first <= vec[i].second) continue;
        
        ll ans = INF;
        ll j = ven.lb(vec[i].first-vec[i].second);
        
        if(j == INF){
            ans = 0;
        }else if(j == -1){

        }else{

        }
        seg.update(i, {seg.query(i,j).val+1});
        ven.dbg();
    }


    forn(i,0,15) cout << i << " " << ven.lb(i) << ln;
    trace(cout << "----------------------------\n\n";)
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
