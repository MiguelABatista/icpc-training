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

v64 id = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
// v64 id = {0,1,2,3,4,5};

// Segment Tree (Range Query + Point Update)
//
//supports point updates and range queries.
//
// complexity: O(log N) per op, O(N)

struct node {
    v64 perm = id;
    
    static node comb(const node& a, const node& b) {
        node comb;

        forn(i, 0, sz(id)) comb.perm[i] = a.perm[b.perm[i]];
        return comb;
    }

    void print(){
        ll n = sz(perm);
        vector<bool> vis(n, false);
        forn(i, 0, n){
            if(vis[i]) continue;
            cout << "( ";
            ll aux = i;
            while(!vis[aux]){
                cout << aux+1 << " ";
                vis[aux] = true;
                aux = perm[aux];
            }
            cout << ") ";
        }
        cout << ln;
    }
};

node transpos(ll i){
    node t;
    t.perm[i] = i+1;
    t.perm[i+1] = i;
    return t;
}

ll ciclos(node& p){
    ll n = sz(p.perm), cnt = 0;
    vector<bool> vis(n, false);
    forn(i, 0, n){
        if(vis[i]) continue;
        // debug(i);
        ll aux = i;
        while(!vis[aux]){
            // debug(aux);
            vis[aux] = true;
            aux = p.perm[aux];
        } 
        cnt++; 
    }

    return cnt;
}   

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
    _; ll n, h, q; cin >> n >> h >> q;
    node neutral;
    segtree<node> seg(h, neutral);

    forn(i, 0, q){
        ll y, x1, x2; cin >> y >> x1 >> x2;

        y--;
        x1--;
        x2--;
        trace(cout << ln << ln << y << " " << x1 << " " << x2 << ln);

        node velho = seg.query(y,y);
        node novo = node::comb(velho, transpos(min(x1,x2)));

        trace(
            debugv(velho.perm);
            velho.print();
            debugv(novo.perm);
            novo.print();
        );

        seg.update(y, novo);

        // debug(y);
        // debugv(transpos(min(x1,x2)).perm);

        // trace(
        //     forn(j, 0, h){
        //         debug(j);  
        //         node qu = seg.query(j,j);
        //         debugv(qu.perm);
        //         qu.print();
        //     }
        //     cout << ln << ln;
        // );

        node total = seg.query(0, h-1);

        trace(cout << "          : 0 1 2 3 4 5" << ln;);
        debugv(total.perm);
        trace(total.print(););
        cout << sz(id) - ciclos(total) << ln;
    }
 
    return 0;
}