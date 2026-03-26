// Perfomance geral (seguro p/ CP)
 #pragma GCC optimize("O3,unroll-loops,fast-math")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double ld;
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
const ld pi = 2*acos(0.0);

const ld DINF = 1e18;
const ld eps = 1e-9;

#define sq(x) ((x)*(x))

int cmp(double x, double y = 0, double tol = eps) {
	return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

struct pt { // ponto
	ld x, y;
	pt(ld x_ = 0, ld y_ = 0) : x(x_), y(y_) {}
	bool operator < (const pt p) const {
		if (cmp(x, p.x) != 0) return cmp(x, p.x) < 0;
		if (cmp(y, p.y) != 0) return cmp(y, p.y) < 0;
		return 0;
	}
	bool operator == (const pt p) const {
		return cmp(x, p.x) == 0 and cmp(y, p.y) == 0;
	}
	pt operator + (const pt p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt p) const { return pt(x-p.x, y-p.y); }
	pt operator * (const ld c) const { return pt(x*c  , y*c  ); }
	pt operator / (const ld c) const { return pt(x/c  , y/c  ); }
	ld operator * (const pt p) const { return x*p.x + y*p.y; }
	ld operator ^ (const pt p) const { return x*p.y - y*p.x; }
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
};

struct line { // reta
	pt p, q;
	line() {}
	line(pt p_, pt q_) : p(p_), q(q_) {}
	friend istream& operator >> (istream& in, line& r) {
		return in >> r.p >> r.q;
	}
};

ld sarea(pt p, pt q, pt r) { // area com sinal
	return ((q-p)^(r-q))/2;
}

bool ccw(pt p, pt q, pt r) { // se p, q, r sao ccw
	return cmp(sarea(p, q, r),0) >= 0;
}

ld get_t(pt v, line r) { // retorna t tal que t*v pertence a reta r
	return (r.p^r.q) / ((r.p-r.q)^v);
}

pt inter(line r, line s) { // r inter s
	if (cmp((r.p - r.q) ^ (s.p - s.q), 0) == 0) return pt(DINF, DINF);
	r.q = r.q - r.p, s.p = s.p - r.p, s.q = s.q - r.p;
	return r.q * get_t(r.q, s) + r.p;
}

line convert(ll a, ll b){
    pt q = {0.0, 1.0/b}; // invertido
    pt p = {1.0/a, 0.0};
    trace(
        cout << "[" << q.x << " " << q.y << "]" << ln;
        cout << "[" << p.x << " " << p.y << "]" << ln;
        cout << ln;
    );
    return line(p,q);
}

int quad(pt p) { // quadrant of a point
    return (p.x<0)^3*(p.y<0);
}

bool compare_angle(pt p, pt q) { // returns true if angle(p) < angle(q)
    if (quad(p) != quad(q)) return quad(p) < quad(q);
    return ccw(q, pt(0, 0), p);
}

bool compare_angle_line(line l, line k){
    return compare_angle(l.q-l.p, k.q-k.p);
}

bool in(line l, pt p){
    ld x = l.p.x;
    ld y = l.q.y;
    ld aux = p.x*y + p.y*x;
    return cmp(aux, x*y) <= 0;
}

vector<pt> hp_intersection(vector<line> &v) {
	deque<pt> dq = {{1, 1}, {0, 1}, {0, 0}, {1, 0}};

	sort(v.begin(), v.end(), compare_angle_line);

	for(int i = 0; i < v.size() and dq.size() > 1; i++) {
		pt p1 = dq.front(), p2 = dq.back();
		while (dq.size() and !in(v[i], dq.back())){//  !ccw(v[i].p, v[i].q, dq.back())
            p1 = dq.back(), dq.pop_back();
        }

		while (dq.size() and !in(v[i], dq.front())) // !ccw(v[i].p, v[i].q, dq.front())
			p2 = dq.front(), dq.pop_front();

        debug(tt);
		if (!dq.size()) break;
		if (p1 == dq.front() and p2 == dq.back()) continue;
		dq.push_back(inter(v[i], line(dq.back(), p1)));
		dq.push_front(inter(v[i], line(dq.front(), p2)));

		if (dq.size() > 1 and dq.back() == dq.front()) dq.pop_back();
	}
	return vector<pt>(dq.begin(), dq.end());
}

int main(){
    _;
    ll n, p, q; 
    cin >> n >> p >> q;
    v64 a(n);
    v64 b(n);

    forn(i,0,n) {
        cin >> a[i];
        cin >> b[i];
    }

    vector<line> linhas(n);
    forn(i,0,n) linhas[i] = convert(a[i], b[i]);

    auto resp = hp_intersection(linhas);

    ld ans = 0;
    for(pt point: resp){
        ans = max(ans, point.x *p + point.y*q);
    }

    cout << fixed << setprecision(15) << ans << ln;
    return 0;
}