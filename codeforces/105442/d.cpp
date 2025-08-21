#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef p64 pt;
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
    #define debugp(x) cout << __LINE__ << ": " << #x << " = " << x.first << " " << x.second << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
    #define debugp(x) (void)0
#endif


const ll INF = 0x3f3f3f3f3f3f3f3fll;

inline p64 inv(p64 p){
    return {p.second, p.first};
}

ll area2(pt p, pt q, pt r){
    // q ^ (r-q)
    pt dif1 = {q.first - p.first, q.second - p.second};
    pt dif2 = {r.first - q.first, r.second - q.second};
    return dif1.first*dif2.second - dif1.second*dif2.first;
}

ll polarea2(vector<pt> v){
    ll ret = 0;
    forn(i,0,v.size()){
        ret += area2(pt(0,0), v[i], v[(i+1)%(ll)v.size()]);
    }
    return ret;
}

int main(){
    _;
    ll n; cin >> n;
    set<p64> ordx;
    set<p64> ordy;

    forn(i,0,n){
        ll x, y;
        cin >> x >> y;
        ordx.emplace(x,y);
        ordy.emplace(y,x);
    }

    forn(i,0,n/4-1){
        if(prev(ordx.end())->first == prev(prev(ordx.end()))->first){
            p64 pa1,pa2,pb1,pb2;
            pa1 = *prev(ordx.end());
            pa2 = *prev(prev(ordx.end()));
            pb1 = *ordx.begin();
            pb2 = *next(ordx.begin());
            ordx.erase(pa1);
            ordx.erase(pa2);
            ordx.erase(pb1);
            ordx.erase(pb2);
            
            ordy.erase(inv(pa1));
            ordy.erase(inv(pa2));
            ordy.erase(inv(pb1));
            ordy.erase(inv(pb2));
        }else{
            p64 pxa, pxb, pya, pyb;
            pxa = *prev(ordx.end());
            pxb = *ordx.begin();
            
            pya = *prev(ordy.end());
            pyb = *ordy.begin();
            
            ordx.erase(pxa);
            ordx.erase(pxb);
            ordx.erase(inv(pya));
            ordx.erase(inv(pyb));
        
            ordy.erase(inv(pxa));
            ordy.erase(inv(pxb));
            ordy.erase(pya);
            ordy.erase(pyb);
        }
    }

    if(prev(ordx.end())->first == prev(prev(ordx.end()))->first){
        p64 pa1,pa2,pb1,pb2;
        pa1 = *prev(ordx.end());
        pa2 = *prev(prev(ordx.end()));
        pb2 = *next(ordx.begin());
        pb1 = *ordx.begin();

        // for(auto p: ordx) debugp(p);
        cout << abs(pa1.second-pb1.second)*abs(pa1.first - pb2.first) << ln;

    }else{
        p64 pxa, pxb, pya, pyb;
        pxa = *prev(ordx.end());
        pxb = *ordx.begin();
        
        pya = *prev(ordy.end());
        pyb = *ordy.begin();
        
        auto vec = {pxa, inv(pya), pxb, inv(pyb)};

        cout << polarea2(vec)/2 << ln; 
    }        
    return 0;
}