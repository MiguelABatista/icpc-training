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

struct node {
    ll val = 0;
    static node comb(const node& a, const node& b) {
        return {a.val+b.val};
    }
};

template<typename T> struct segtree {
    ll n;
    T neutral;
    vector<T> tree;

    segtree(ll _n, T _neutral=  T()) {
        n = _n, neutral = _neutral;
        tree.resize(2*n+1, neutral);
    }

    void set_leaves(vector<T> &leaves) {
        copy(leaves.begin(), leaves.end(), tree.begin() + n);
        
        for (ll i = n-1; i > 0; i--) tree[i] = T::comb(tree[2*i], tree[2*i + 1]);
    }

    void update(ll i, T v){
        i += n;
        tree[i] = T::comb(tree[i], v);
        while (i > 1){
            i /= 2;
            tree[i] = T::comb(tree[2*i], tree[2*i + 1]);
        }
    }

    void set(ll i, T v){
        i += n;
        tree[i] = v;
        while (i > 1){
            i /= 2;
            tree[i] = T::comb(tree[2*i], tree[2*i + 1]);
        }
    }
    T query(ll i, ll j){
        T rl = neutral, rr = neutral;
        for(i += n, j += n; i <= j; i /= 2, j /= 2){
            if((i&1) == 1) rl = T::comb(rl, tree[i++]);
            if((j&1) == 0) rr = T::comb(tree[j--], rr);
        }
        return T::comb(rl, rr);
    }
};

void print(segtree<node>& s, ll n){
    forn(i,0,n) cout << s.query(i,i).val << " \n"[i==n-1];
}

int main() {
    _;
    ll n, q; cin >> n >> q;
    vll vec(2*n);

    forn(i,0,n){
        cin >> vec[i];
        vec[i+n] = vec[i];
    }

    segtree<node> inv(n+1, {0});
    segtree<node> inv2(n+1, {0});
    segtree<node> segindo(2*n, {0});
    segtree<node> segvindo(2*n, {0});

    
    forn(i,0,2*n){
        inv.update(vec[i], {1});
        ll val = inv.query(vec[i]+1, n).val;
        if(i >= n) val = n-vec[i];
        segindo.update(i, {val});
    }
    
    for(ll i = 2*n-1; i>= 0; i--){
        inv2.update(vec[i], {1});
        ll val = inv2.query(0, vec[i]-1).val;
        if(i < n) val = vec[i] - 1;
        segvindo.update(i, {val});
    }

    trace(print(segindo, 2*n);)
    trace(print(segvindo, 2*n);)

    while (q--){
        ll t; cin >> t;
        if(t == 1){
            ll idx; cin >> idx;
            idx--;
            // troca idx e idx+1;
            if(vec[idx] < vec[idx+1]){
                segindo.update(idx+1,{1});
                segvindo.update(n+idx, {1});            
            }else{
                segindo.update(idx+1,{-1});
                segvindo.update(n+idx,{-1});
            }
            swap(vec[idx], vec[idx+1]);
            swap(vec[idx+n], vec[idx+1+n]);
            segindo.set(idx+n,{n-vec[idx]});
            segindo.set(idx+1+n,{n-vec[idx+1]});
            segvindo.set(idx,{vec[idx]-1});
            segvindo.set(idx+1,{vec[idx+1]-1});
        }else{
            ll k; cin >> k;
            ll resp = segindo.query(0,n-1+k).val - (k == 0 ? 0 : segvindo.query(0,k-1).val);
            cout << resp << ln;
        }
    }
     
    return 0;
}
