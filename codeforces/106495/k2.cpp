#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
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
const ld DINF = 1e18;
const ld eps = 1e-9;
const ld pi = 2*acos(0);

ll cmp(ld x, ld y = 0, ld tol = eps){
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

struct pt {
    ld x, y;
    pt(ld x_ = 0, ld y_ = 0) : x(x_), y(y_) {}
    bool operator < (const pt p) const {
        if(cmp(x, p.x) != 0) return cmp(x, p.x) < 0;
        if(cmp(y, p.y) != 0) return cmp(y, p.y) < 0;
        return 0;
    }

    bool operator == (const pt p) const {
        return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
    }
    pt operator + (const pt p) const { return pt(x + p.x, y + p.y);}
    pt operator - (const pt p) const { return pt(x - p.x, y - p.y);}
    pt operator * (const ld c) const { return pt(x*c, y*c);}
    pt operator / (const ld c) const { return pt(x/c, y/c);}
    ld operator * (const pt p) const { return x*p.x + y*p.y;}
    ld operator ^ (const pt p) const { return x*p.y - y*p.x;}

    friend istream& operator >> (istream& in, pt& p) {
        return in >> p.x >> p.y;
    }
};

struct line {
    pt p, q;
    line() {}
    line(pt p_, pt q_) : p(p_), q(q_) {}
};

ld norm_sq(pt p){ return p*p;}

ld norm(pt p){ return sqrt(norm_sq(p));}

ld dist_sq(pt p, pt q){ return norm_sq(p - q);}

ld dist(pt p, pt q){ return sqrt(dist_sq(p,q));}

ld sarea(pt p, pt q, pt r) {
    return ((q-p)^(r-q))/2;
}

bool ccw(pt p, pt q, pt r, bool strict = true) {
    return cmp(sarea(p, q, r)) > 0 || (!strict && cmp(sarea(p, q, r)) == 0);
}

ld angle(pt v) {
    ld ang = atan2(v.y, v.x);
    if(cmp(ang, 0) < 0) ang += 2*pi;
    return ang;
}

pair<pt, pt> perp_pts(line l, ld d){
    pt dir = l.p - l.q;
    pt r = pt(dir.y, -dir.x);
    pt k = r*(d/norm(r));
    return {l.q + k, l.q - k};
}

pair<pt, pt> circint(pt o1, ld r1, pt o2, ld r2){
    pt dir = o2 - o1;
    pt in(DINF, DINF);
    ld d = norm(dir);

    if(cmp(r1 + r2, d) == 0 || cmp(d+r2, r1) == 0 || cmp(d+r1, r2) == 0)
        return {o1 + dir*r1/(r1+r2), in};

    if(cmp(r1+r2, d) == -1 || cmp(d+r2, r1) == -1 || cmp(d+r1, r2) == -1)
        return {in, in};

    ld x = (d*d - r2*r2 + r1+r1)/(2*d);
    return perp_pts(line(o1, o1 + dir * x/d), sqrt(r1*r1 - x*x));
}   

ld solve(ll ind, pt p, vector<pt>& center, vector<ld>& radius){
    ll n = sz(center);
    map<pair<ld, ll> , pair<ll,pt>> sweep;
    ll curr = 0;

    forn(i, 0, n){
        if(i == ind) continue;
        auto [p1, p2] = circint(center[ind], radius[ind], center[i], radius[i]);

        if(ccw(center[i], p2, p1)) swap(p1, p2);
        ld ang1 = angle(p1 - center[ind]);
        ld ang2 = angle(p2 - center[ind]);

        sweep[{ang1, 1}].first++;
        sweep[{ang1, 1}].second = p1;
        sweep[{ang2, 0}].first++;
        sweep[{ang2, 1}].second = p2;

        curr += (cmp(ang1, ang2) > 0);
    }

    pt l, r;

    if(curr == n-1){
        l = (*sweep.rbegin()).second.second;
        r = (*sweep.begin()).second.second;
    } else {
        for(auto s = sweep.begin(); s!= sweep.end(); s++){
            auto [pp, qq] = *s;
            auto [ang, open] = pp;
            auto [freq, point] = qq;
            if(open == 0){
                curr -= freq;
                continue;
            }

            curr += freq;
            if(curr == n-1){
                l = point;
                r = next(s)->second.second;
                break;
            }
        }
    }

    debug(ind);
    debug(l.x);
    debug(l.y);
    debug(r.x);
    debug(r.y);


    ld dl = dist(l, p), dr = dist(r, p), dc = dist(center[ind], p) - radius[ind];
    ld min_d;

    debug(dl);
    debug(dc);
    debug(dr);

    if(cmp(dl, dr) < 0) min_d = dl;
    else min_d = dr;
    
    if(ccw(center[ind], l, p) && !ccw(center[ind], r, p) && cmp(min_d, dc) > 0) min_d = dc;

    return min_d;
}

int main() {
    _; ll n; cin >> n;
    pt p; cin >> p;
    vector<pt> center(n);
    vector<ld> radius(n);

    forn(i, 0, n){
        cin >> center[i];
        cin >> radius[i];
    }

    bool outside = false;
    forn(i, 0, n){
        if(cmp(dist(p, center[i]),radius[i]) > 0) outside = true;
    }

    if(!outside){
        cout << 0 << ln;
        return 0;
    }

    ld best_dist = DINF;
    forn(i, 0, n){
        ld dist = solve(i, p, center, radius);
        if(cmp(dist, best_dist) < 0) best_dist = dist;
    }

    cout << fixed << setprecision(20) << best_dist << ln;

    return 0;
}
