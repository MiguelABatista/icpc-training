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
    ll val = -INF;
    
    static node comb(const node& a, const node& b) {
        return {max(a.val, b.val)};
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

    void print(){
        forn(i,n,2*n) cout << tree[i].val << " ";; cout << ln;   
    }
};

int main() {
    _;
    ll n, q; cin >> n >> q;

    v64 vec(n);
    vector<node> vaux(n);
    map<ll,set<ll>> idxs;

    map<ll, ll> mp;
    forn(i,0,n){
        cin >> vec[i]; 
        auto it = mp.find(vec[i]);
        if(it == mp.end()) vaux[i].val = -1;
        else vaux[i].val = it->second;
        mp[vec[i]] = i;
        idxs[vec[i]].insert(i);
    } 
    segtree seg(n, node());
    seg.set_leaves(vaux);

    while(q--){
        trace(seg.print(););
        ll t; cin >> t;
        if(t == 1){
            ll k, u;
            cin >> k >> u;
            k--;
            if(vec[k] == u) continue;
            // fix old
            ll old = vec[k];
            auto& s = idxs[old];
            auto it = s.find(k);
            auto rit = next(it);
            if(rit != s.end()){
                seg.update(*rit, {
                    (it != s.begin() ? *prev(it) : -1)
                });
            }
            s.erase(it);

            // add new            
            auto& ss = idxs[u];
            it = ss.lower_bound(k);
            seg.update(k, {
                (it != ss.begin() ? *prev(it) : -1)
            });
            if(it != ss.end()) seg.update(*it, {k});

            ss.insert(k);
            vec[k] = u;
        }else{
            ll a, b;
            cin >> a >> b;
            a--, b--;
            ll m = seg.query(a,b).val;
            debug(m);
            if(m >= a) cout << "NO" << ln;
            else cout << "YES" << ln;
        }
    }
    return 0;
}
