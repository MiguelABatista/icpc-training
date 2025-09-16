#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"
#define sq(x) ((x)*(ll)(x))

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

struct pt {
    ll x, y;
    pt(ll x_ = 0, ll y_ = 0) : x(x_), y(y_) {}
    bool operator == (const pt p) const {
        return x == p.x and y == p.y;
    }
    pt operator + (const pt p) const { return pt(x+p.x, y+p.y); }
    pt operator - (const pt p) const { return pt(x-p.x, y-p.y); }
    pt operator * (const ll c) const { return pt(x*c, y*c); }
    ll operator * (const pt p) const { return x*(ll)p.x + y*(ll)p.y; }
    ll operator ^ (const pt p) const { return x*(ll)p.y - y*(ll)p.x; }
    friend istream& operator >> (istream& in, pt& p){
        return in >> p.x >> p.y;
    }
};

struct line {
    pt p, q;
    line() {}
    line(pt p_, pt q_) : p(p_), q(q_) {}

    bool operator == (const line l) const {
        return p == l.p and q == l.q;
    }
};

ld dist(pt p, pt q){
    return sqrt(sq(p.x-q.x)+sq(p.y - q.y));
}

ll sarea2(pt p, pt q, pt r){
    return (q-p)^(r-q);
}

bool ccw(pt p, pt q, pt r){
    return sarea2(p, q, r) >= 0;
}

bool isinseg(pt p, line r){
    pt a = r.p - p, b = r.q -p;
    return (a^b) == 0 and (a*b) <= 0;
}

bool interseg(line r, line s){
    if(isinseg(r.p, s) or isinseg(r.q, s) or isinseg(s.p, r) or isinseg(s.q, r)) return 1;
    return ccw(r.p, r.q, s.p) != ccw(r.p, r.q, s.q) and ccw(s.p, s.q, r.p) != ccw(s.p, s.q, r.q);
}

int main() {
    _; ll n; cin >> n;
    vector<line> poly(n);
    vector<pt> point(n+1);
    vector<vector<pair<ll, ld>>> g(n+1);
    forn(i, 0, n){
        cin >> point[i];
        if(i == 0) continue;
        poly[i] = line(point[i], point[i-1]);
    }
    poly[0] = line(point[0], point[n-1]);

    cin >> point[n];

    forn(i, 0, n){
        forn(j, 0, i){
            line l = line(point[i], point[j]);
            bool deu_merda = false;
            forn(k, 0, n){
                if(k == i or k == (i+1)%n or k == j or k == (j+1)%n) continue;
                line l2 = poly[k];
                if(interseg(l, l2) and !(l == l2)){
                    cout << l.p.x << " " << l.p.y << " " << l.q.x << " " << l.q.y << ln;
                    cout << k << ln;
                    cout << ln;
                    deu_merda = true;
                }
            }
            if(!deu_merda){
                g[i].push_back({j, dist(i, j)});
                g[j].push_back({i, dist(i, j)});
                
                cout << i << " " << j << ln;
            }
            // cout << ln;
        }
    }

    

    return 0;
}