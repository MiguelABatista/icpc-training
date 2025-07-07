#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
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

const ld INF = ((ld)2e18)*((ld)2e18);

struct pt {
    ll x0, y0, vx, vy;

    pair<ld,ld> pos(ld t) {
        return {(ld)x0 + t*vx, (ld)y0 + t*vy};
    }
};


int main(){
    _;
    ll n; cin >> n;
    vector<pt> pts(n);
    forn(i, 0, n) {
        ll x, y, vx, vy; cin >> x >> y >> vx >> vy;
        pts[i].x0 = x;
        pts[i].y0 = y;
        pts[i].vx = vx;
        pts[i].vy = vy;
    }

    function<ld (ld)> rec = [&](ld t) {
        ld x0 = INF, x1 = -INF, y0 = INF, y1 = -INF;
        forn(i, 0, n) {
            auto p = pts[i].pos(t);
            x0 = min(x0, p.first);
            x1 = max(x1, p.first);
            y0 = min(y0, p.second);
            y1 = max(y1, p.second);
        }
        return (x1 - x0) * (y1 - y0);
    };

    ld l = 0, r = ((ld)2e18) * 4;
    ld sa = rec(l);
    ld se = rec(r);
    forn(i, 0, 200) {
        ld intervalo = (r-l)/4;
        ld a = sa;
        ld b = rec(l + 1 * intervalo);
        ld c = rec(l + 2 * intervalo);
        ld d = rec(l + 3 * intervalo);
        ld e = se;
        ld mn = min({a, b, c, d, e});
        if (a == mn) {
            r = l+1*intervalo;
            se = b;
            continue;
        }
        if (b == mn) {
            r = l+2*intervalo;
            se = c;
            continue;
        }
        if (c == mn) {
            l = l+1*intervalo;
            r = l+3*intervalo;
            sa = b;
            se = d;
            continue;
        }
        if (d == mn) {
            l = l +2*intervalo;
            sa = c;
            continue;
        }
        l = l+3*intervalo;
        sa = d;
    }
    cout << fixed << setprecision(50) << rec(l) << ln;

    return 0;
}