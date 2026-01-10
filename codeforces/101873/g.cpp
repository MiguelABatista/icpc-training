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

struct pt {
    ll x, y;
    pt(ll x_ = 0, ll y_ = 0) : x(x_), y(y_) {}

    pt operator - (const pt p) const { return pt(x-p.x, y-p.y);}
    ll operator ^ (const pt p) const { return x*(ll)p.y - y*(ll)p.x; }

    friend istream& operator >> (istream& in, pt& p){
        return in >> p.x >> p.y;
    }
};

ll sarea2(pt p, pt q, pt r){
    return (q-p)^(r-q);
}

ll polarea2(vector<pt> v){
    ll ret = 0;
    forn(i, 0, sz(v)){
        ret+= sarea2(pt(0,0), v[i], v[(i+1)%sz(v)]);
    }
    return abs(ret);
}

int main(){
    _; ll n; cin >> n;
    vector<pt> pol(n);
    forn(i, 0, n) cin >> pol[i];

    ll s2 = polarea2(pol);

    ll borda = n;
    forn(i, 0, n){
        ll x = pol[i].x - pol[(i-1+n)%n].x;
        ll y = pol[i].y - pol[(i-1+n)%n].y;

        borda += gcd(x,y)-1;
    }

    ll interior = s2 - borda + 2;
    cout << interior/2 << ln;
    
    return 0;
}