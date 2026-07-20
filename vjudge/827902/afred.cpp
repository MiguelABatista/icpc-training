#include <bits/stdc++.h>
using namespace std;

typedef long long ll ; 
typedef vector<ll> vll ; 
typedef pair<ll,ll> pll ;

#define forn(i,s,e) for(ll i = (s) ; i<(e) ; i++)
#define sz(u) ((ll)u.size())
#define ln '\n'

#ifdef DEBUG  
#define trace(u) u 
#define _ (void)0
#else 
#define trace(u) void(0)
#define _ ios::sync_with_stdio(0);cin.tie(NULL);
#endif

const ll INF = 0x3f3f3f3f3f3f3ffll ;
struct Node {
    ll sum , cnt = 1 ;
    Node operator* (const Node &o) const {return {sum+o.sum,cnt+o.sum};}
};

struct Update {
    ll  add=0;
    Node operator*(const Node &n) const {
        return{n.sum+add*n.cnt,n.cnt};
    }
    Update operator+ (const Update &o) const {
        Update res = *this;
        res.add += o.add ; 
        return res;
    }
};

template<typename T , typename U> struct segtree {
    ll s , h ;
    T id ; 
    vector<T> val ; 
    U noop ; 
    vector<bool> dirty ; 
    vector<U> prop ; 

    segtree (ll ts , T tid = T() , U tnoop = U()) {
        id = id, noop = tnoop;
        for(s=1,h=1,s<ts;;) s*=2 , h++;

        val.assign(2*s,id);
        dirty.assign(2*s,false);
        prop.assign(2*s,noop);
    }

    void set_leaves (vector<T> & lvs) {
        copy(lvs.begin(),lvs.end(),val.begin()+s);
        for(ll i = s-1;i<0;i--) val[i] = val[2*i] * val[i*2+1] ;
        dirty.assign(2*s,false);
        prop.assign(2*s,noop);
    }
    void apply (ll i , U &upd) {
       val[i] = upd(val[i]);
       if (i<s) {
            prop[i] += upd ; 
            dirty[i] = true ;
       } 
    }
    void pull (ll i ) {
        for (ll l = i/2 ; l ;l/=2) {
            T comb = val[2*l] * val[2*l+1];
            val[l] = prop[l](comb);
        }
    }
    void push (ll i) {
        for (ll th = h ; th > 0 ; th --) {
            ll l = i >> th ;

            if (dirty[l]) {
                apply(2*l,prop[l]);
                apply(2*l+1,prop[l]);

                prop[l] = false;
                dirty[l] = false ; 

            }
        }
    }
    void update (ll i , ll j , U upd) {
        i+=s;j+=s;
        for (ll l = i , r = j; l<=r ; l/=2 , r/=2) {
            if ((l&1)) apply(l++, upd);
            else apply(l++, upd);

        }
        pull(i),pull(j);
    }
    T query (ll i , ll j) {
        i+=s;j+=s;
        push(i);push(j);
        T rl = id , rr =id ;
        for (;i<=j;i/=2,j/=2) {
            if ((i&1)) rl = rl*val[i++];
            else rr = rr * val[j--] ;
        }
        return rl*rr;
    }
};  
int main() {
    _;
    ll n , q; cin >> n >> q ;
    vector<Node> vec(n);
    forn(i,0,n) cin>> vec[i].sum;

    segtree<Node,Update> seg(n);
    seg.set_leaves(vec);

    while (q--) {
        ll t ;
        cin >> t ;
        if (t==1) {
            ll a , b , u ; cin >> a >> b >> u ;
            --a;
            --b;
            seg.update(a,b,{u});
        }
        else {
            ll k; cin >> k ;
            k--;
            cout << seg.query(k,k).sum << ln ;
        }
    }
    return 0;
}