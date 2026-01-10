#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
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

#define debugv(v) trace({cout << #v": "; for (auto u : v) cout<< u << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ld eps = 0.001;
const ll POW = 1000000;

struct pt {
    ll x, y;
    pt(ll x_ = 0, ll y_ = 0) : x(x_), y(y_) {}
    bool operator < (const pt p) const {
        if(x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator == (const pt p) const {
        return x == p.x and y == p.y;
    }
    bool operator != (const pt p) const {
        return x != p.x or y != p.y;
    }
    pt operator + (const pt p) const { return pt(x+p.x, y+p.y); }
    pt operator - (const pt p) const { return pt(x-p.x, y-p.y); }
    pt operator * (const ll c) const { return pt(x*c, y*c); }
    ll operator * (const pt p) const { return x*(ll)p.x + y*(ll)p.y; }
    ll operator ^ (const pt p) const { return x*(ll)p.y - y*(ll)p.x; }
    friend istream& operator >> (istream& in, pt& p) {
        return in >> p.x >> p.y;
    }
    friend ostream& operator << (ostream& out, pt& p) {
        return out << p.x << "," << p.y;
    }
};

ll sarea2(pt p, pt q, pt r) {
    return (q-p)^(r-q);
}

bool ccw(pt p, pt q, pt r) {
    return sarea2(p, q, r) > 0;
}

ll quad(pt p){
    return (p.x<0)^3*(p.y<0);
}

bool compare_angle(pt p, pt q){ // return p < q;
    if(quad(p) != quad(q)) return quad(p) < quad(q);
    return ccw(q, pt(0,0), p);
}

vector<pt> convex_hull(vector<pt>& v){
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(),v.end()), v.end());
    if(v.size() <= 1) return v;
    vector<pt> l, u;
    for(ll i = 0; i < sz(v); i++){
        while(l.size() > 1 and !ccw(l.end()[-2], l.end()[-1], v[i]))
            l.pop_back();
        l.push_back(v[i]);
    }

    for(ll i = sz(v)-1; i>= 0; i--){
        while(u.size() > 1 and !ccw(u.end()[-2], u.end()[-1], v[i]))
            u.pop_back();
        u.push_back(v[i]);
    }

    l.pop_back(); u.pop_back();
    for(pt i : u) l.push_back(i);
    return l;
}

ll n;
vector<pt> choc;

ll windmill(pt orig, pt ini, pt fim){
    vector<pt> sweep;
    forn(i, 0, n) sweep.push_back(choc[i] - orig);
    // sweep.push_back(ini-orig);
    // sweep.push_back(fim-orig);

    sort(sweep.begin(), sweep.end(), compare_angle);
    
    ll mod = sweep.size();

    // auto prox = [&](ll& o){o = (o+1)%mod;};

    ll l = upper_bound(sweep.begin(), sweep.end(), ini-orig, compare_angle) - sweep.begin();
    ll r_final = upper_bound(sweep.begin(), sweep.end(), fim-orig, compare_angle) - sweep.begin();
    
    if(r_final <= l) r_final += mod;

    ll r = l;
    
    ll best = 0;
    debug(orig);
    debug(l);
    debug(r_final);
    debugv(sweep);
    
    while (r != r_final){
        debug(r);
        debug(l);
        debug(r_final);
        // ll x; cin >> x;
        // cout << x << ln;
        if(sarea2(pt(0,0), sweep[l%mod], sweep[r%mod]) == 0){
            r++;
        }else if (ccw(pt(0,0), sweep[l%mod], sweep[r%mod])) r++;
        else{
            debug("LAMBARI");
            best = max(best, r-l);
            l++;
        }
    }
    best = max(best, r-l);
    return best;
}

int main(){
    _; ll m; cin >> n >> m;
    choc.resize(n);
    vector<pt> strawb(m);

    forn(i, 0, n){
        ld a, b; cin >> a >> b;
        a = POW*a+eps;
        b = POW*b+eps;
        choc[i] = pt(a, b);
    }
    forn(i, 0, m){
        ld a, b; cin >> a >> b;
        a = POW*a+eps;
        b = POW*b+eps;
        strawb[i] = pt(a, b);
    }

    strawb = convex_hull(strawb);
    m = sz(strawb);

    ll best_cut = 0; 
    forn(i, 0, m){
        best_cut = max(best_cut, windmill(strawb[i], strawb[(i+1)%m], strawb[(i-1+m)%m]));
    }

    cout << best_cut<< ln;

    return 0;
}