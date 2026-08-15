#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for (ll i=(s); i<(e); i++)
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
#define debugv(v) trace(cout << #v ": "; for(auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

struct pt {
    ll x, y;
    pt(ll x_ = 0, ll y_ = 0) : x(x_), y(y_) {};

    pt operator + (const pt p) const { return pt(x+p.x, y+p.y);}    
    pt operator - (const pt p) const { return pt(x-p.x, y-p.y);}    
    ll operator ^ (const pt p) const { return x*(ll)p.y - y*(ll)p.x;}
};

ll sarea2(pt p, pt q, pt r){
    return (q-p)^(r-q);
}

bool ccw(pt p, pt q, pt r, bool strict = false){
    return sarea2(p,q,r) > 0 || (!strict && sarea2(p,q,r) == 0);
}

void solve(){
    ll n; cin >> n;
    vector<pt> vec(n);
    forn(i,0,n) cin >> vec[i].x >> vec[i].y;
    
    ll l = 3;
    ll r = n;
    ll ans = 3;

    vector<bool> bom_vert(n, false), acc(n, 0);

    forn(i, 1, n-1){
        bom_vert[i] = !ccw(vec[i-1], vec[i], vec[i+1]);
    }

    forn(i, 1, n) acc[i] = bom_vert[i] + acc[i-1];
    
    auto bom_inter = [&](ll l, ll r){
        
    }

    auto testa = [&](ll k){
        return true;
    };
    
    while(l <= r){
        ll m = (l+r)/2;
        if(testa(vec,n, m)){
            ans = m;
            l = m + 1;
        }else{
            r = m-1;
        }
    }

    cout << ans << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}