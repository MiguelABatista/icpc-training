#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Geometria 3D
 
typedef double ld;
const ld DINF = 1e18;
const ld eps = 1e-9;
 
#define sq(x) ((x)*(x))

 
bool eq(ld a, ld b) {
    return abs(a - b) <= eps;
}
 
struct pt { // ponto
    ld x, y, z;
    pt(ld x_ = 0, ld y_ = 0, ld z_ = 0) : x(x_), y(y_), z(z_) {}
    bool operator < (const pt p) const {
        if (!eq(x, p.x)) return x < p.x;
        if (!eq(y, p.y)) return y < p.y;
        if (!eq(z, p.z)) return z < p.z;
        return 0;
    }
    bool operator == (const pt p) const {
        return eq(x, p.x) and eq(y, p.y) and eq(z, p.z);
    }
    pt operator + (const pt p) const { return pt(x+p.x, y+p.y, z+p.z); }
    pt operator - (const pt p) const { return pt(x-p.x, y-p.y, z-p.z); }
    pt operator * (const ld c) const { return pt(x*c  , y*c  , z*c  ); }
    pt operator / (const ld c) const { return pt(x/c  , y/c  , z/c  ); }
    ld operator * (const pt p) const { return x*p.x + y*p.y + z*p.z; }
    pt operator ^ (const pt p) const { return pt(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x); }
    friend istream& operator >> (istream& in, pt& p) {
        return in >> p.x >> p.y >> p.z;
    }
    friend ostream& operator << (ostream& out, pt p) {
        out << p.x << " " << p.y << " " << p.z;
        return out;
    }
};
 
// distancia
inline ld dist(pt a, pt b) {
    return sqrt(sq(a.x-b.x) + sq(a.y-b.y) + sq(a.z-b.z));
}

inline ld norm(pt a){
    return dist(a, pt(0,0,0));
}

inline bool ccw(pt a, pt b, pt p){
    return ((a^b)*p < 0);
}

inline ld rad(ld a, ld b, ld c){
    ld s = (a+b+c)/2;
    ld dem = sqrt(s*(s-a)*(s-b)*(s-c));
    debug(dem);
    return (a*b*c)/(4*dem);
}

pair<ld, ll> separador(pt a, pt b, pt p){
    pt med = (a+b)/2;
    med = med/norm(med);
    
    ll idx = 0;

    ld r0 = dist(med,a);
    ld r = dist(med, p);

    if(r < r0 + eps) idx += 1;

    idx += 2*ccw(a,b,p);

    ld resp = rad(dist(a, b), dist(b, p), dist(p, a));

    return {resp, idx};
}

ld solve(ll a, ll b, vector<pt>& pontos, ll n){
    vector<ld> vec(4,INF);
    
    if(pontos[a]+pontos[b] == pt(0,0,0)){
        return -1;
    }

    forn(i,0,n){
        if(i == a || i == b) continue;
        debug(i);
        auto [r, idx] = separador(pontos[a], pontos[b], pontos[i]);
        vec[idx] = min(vec[idx], r);
    }

    ld fd = vec[0];
    ld dd = vec[1];
    ld fe = vec[2];
    ld de = vec[3];

    if(dd < DINF-1 && de < DINF-1){
        return -1;
    }

    if(dd < DINF-1){
        return min(dd, fe);
    }
    if(de < DINF-1){
        return min(de, fd);
    }

    return max(fe, fd);
}

int main(){
    _;
    ll n; cin >> n;

    if(n <= 3){
        cout << 90 << ln;
        return 0;
    }

    vector<pt> pontos;
    forn(i,0,n){
        ll x, y, z;
        cin >> x >> y >> z;
        ld r = sqrt(ld(x*x+y*y+z*z));
        pontos.push_back(pt(x/r, y/r, z/r));
    }

    vector<pt> pontos_clean;

    forn(i,0,n){
        bool found = false;
        for(auto p : pontos_clean){
            if(dist(pontos[i], p) < eps){
                found = true;
                break;
            }
        }

        if(!found){
            pontos_clean.push_back(pontos[i]);
        }
    }
    
    swap(pontos, pontos_clean);
    n = pontos.size();
    

    ld best = -1;
    forn(i,0,n){
        forn(j,i+1,n){
            // cout << ln << ln << i << " " << j << ln;
            ld curr_r = solve(i, j, pontos, n);
            debug(curr_r);
            best = max(curr_r, best);
        }
    }

    if(best > DINF-1){
        cout << 90 << ln;
        return 0;
    }

    debug(best);

    cout  << fixed << setprecision(20) << (asin(best) * 180.0) / (2*acos(0.0)) << ln;

    return 0;
}