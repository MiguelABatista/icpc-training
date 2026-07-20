#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
#define forn(i,e,s) for( ll i = (s); i < (e); i++)

struct Node{
    ll sum, cnt=1;
    Node operator*(const Node &o) const { return {sum + o.sum, cnt +o.cnt};}
};

struct Update{
    ll add=0;

    Node operator() (const Node &n) const {
        return {n.sum + add*n.cnt,n.cnt};
    }

    Update operator+ (const Update &o) const {
        Update res = *this;
        res.add+=o.add;
        return res;
    }
};

template<typename T, typename U> struct segtree {
    ll s, h;

    T id;
    vector<T> val;

    U noop;
    vector<bool> dirty;
    vector<U> prop;

    segtree(ll ts, T tid=T(), U tnoop = U()){
        id=tid,noop=tnoop;
        for(s=1,h=1;s<ts;) s*=2,h++;  
        
        val.assign(2*s,id);
        dirty.assign(2*s,false);
        prop.assign(2*s,noop);
    }

    void set_leaves(vector<T> &lvs) {
        copy(lvs.begin(),lvs.end(),val.begin()+s);

        for(ll i=s-1;i>0;i--) val[i]=val[2*i]*val[2*i+1];
        dirty.assign(2*s,false);
        prop.assign(2*s,noop);

    }

    void apply(ll i, U &upd) {
        val[i]=upd(val[i]);
        if(i<s){
            prop[i]=prop[i]+upd;
            dirty[i] = true;
        }
    }

    void pull (ll i){
        for(ll l=i/2; l; l/=2){
            T comb = val[2*l]*val[2*l+1];
            val[l]=prop[l](comb);

        }
    }

    void push(ll i){
        for( ll th = h; th>0; th--){
            ll l=i >> th;

            if(dirty[l]){
                apply(2*l,prop[l]);
                apply(2*l+1,prop[l]);

                prop[l]=noop;
                dirty[l]=false;
            }
        }
    }

    void update(ll i, ll j, U upd){
        i+=s;j+=s;
        push(i),push(j);

        for(ll l=i, r=j; l<=r; l/=2, r/=2)  {
            if((l&1)==1) apply(l++,upd);
            if((r&1)==0) apply(r--,upd);
        }

        pull(i),pull(j);
    }

    T query(ll i, ll j){
        i+=s;j+=s;
        push(i),push(j);

        T rl=id,rr=id;
        for(;i<=j; i/=2, j/=2)  {
            if((i&1)==1) rl=rl*val[i++];
            if((j&1)==0) rr=val[j--]*rr;
        }
        return rl*rr;
    }

};

int main(){
    ll n,q; cin >> n >> q;
    cout << n << "\n";
    vector<Node> vec(n);
    forn(i,0,n) cin >> vec[i].sum;
    
    segtree<Node,Update> seg(n);
    seg.set_leaves(vec);

    cout << n << "\n";
    forn(i,0,n){
        cout << n << "\n";
        cout  << " : ";; cout << endl;
    }
    cout << n << "\n";

    while(q--){
        ll t; cin >> t;
        if(t==1){
            ll a,b,u; cin >> a >> b >> u;
            a--;b--;
            seg.update(a,b,{u});
        }else{
            ll k; cin >> k;
            k--;
            cout << seg.query(k,k).sum << endl;
        }
    }
     return 0;
 }