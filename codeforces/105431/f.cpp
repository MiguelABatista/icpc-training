#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<double> cd;
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
const ll MAXIDX = 1'002'001;

#define sq(x) ((x)*(ll)(x))

struct pt { // ponto
	ll x, y;
	pt(ll x_ = 0, ll y_ = 0) : x(x_), y(y_) {}
	bool operator < (const pt p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
	bool operator == (const pt p) const {
		return x == p.x and y == p.y;
	}
	pt operator + (const pt p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt p) const { return pt(x-p.x, y-p.y); }
	pt operator * (const ll c) const { return pt(x*c, y*c); }
	ll operator * (const pt p) const { return x*(ll)p.x + y*(ll)p.y; }
	ll operator ^ (const pt p) const { return x*(ll)p.y - y*(ll)p.x; }
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
    friend ostream& operator<<(ostream& out, pt p) {
		out << '(' << p.x << ',' << p.y << ')';
		return out;
	}

    ll idx(){
        return 1001*x + y;
    }
};

struct line { // reta
	pt p, q;
    mutable bool visited = false;
	line() {}
	line(pt p_, pt q_) : p(p_), q(q_) {}
	friend istream& operator >> (istream& in, line& r) {
		return in >> r.p >> r.q;
	}
};

ll sarea2(pt p, pt q, pt r) { // 2 * area com sinal
	return (q-p)^(r-q);
}

bool ccw(pt p, pt q, pt r) { // se p, q, r sao ccw
	return sarea2(p, q, r) > 0;
}

ll quad(pt p) { // quadrante de um ponto
	return (p.x<0)^3*(p.y<0);
}

struct compare_ang{
    bool operator()(const line& l, const line& k) const { // retorna se ang(p) < ang(q)
        pt p = l.p - l.q;
        pt q = k.p - k.q;
        if (quad(p) != quad(q)) return quad(p) < quad(q);
        return ccw(q, pt(0, 0), p);
    }
};

ll polarea2(vector<pt>& v) { // 2 * area do poligono
	ll ret = 0;
	for (int i = 0; i < v.size(); i++)
		ret += sarea2(pt(0, 0), v[i], v[(i + 1) % v.size()]);
	return abs(ret);
}

vector<ll> dict(MAXIDX);
vector<pt> vert;
vector<set<line, compare_ang>> graph;

ll find_cycle(pt& goal, pt& beg){
    vector<pt> poly = {goal};
    pt pos_goal = beg;
    pt curr = beg, last = goal;
    do{
        // debug(curr);
        // debug(curr.idx());
        poly.push_back(curr);

        ll i = dict[curr.idx()];
        // debug(i);

        auto nxt = graph[i].upper_bound(line(curr, last));
        if(nxt == graph[i].end()){
            nxt = graph[i].begin();
        }

        if(nxt->visited) return -1;
        nxt->visited = true;
        #ifdef DEBUG
        cout << nxt->p << " : " << nxt->q << ln;
        #endif
        curr = nxt->q;
        last = nxt->p;
    } while(!(curr == beg) || !(last == goal));

    return polarea2(poly);
}


int main(){
    _; ll n; cin >> n;
    set<pt> conj;
    vector<line> edge;

    forn(i, 0, n){
        line l; cin >> l;
        edge.push_back(l);
        edge.push_back(line(l.q, l.p));
        conj.insert(l.p);
        conj.insert(l.q);
    }

    ll cnt = 0;
    for(auto p : conj) dict[p.idx()] = cnt++;
    
    graph.resize(conj.size());

    for(auto l : edge){
        ll i = dict[(l.p).idx()];
        graph[i].insert(l);
    }

    ll best = 0;
    ll sum = 0;
    for(auto l : edge){
        ll area = find_cycle(l.p, l.q);
        if(area == -1) continue;
        debug(l.p);
        debug(l.q);
        debug(area);
        best = max(best, sq(area));
        sum += sq(area);
    }

    // forn(i, 0, conj.size()){
    //     debug(graph[i].begin()->p);
    //     for(auto l : graph[i]){
    //         debug(l.q);
    //     }
    // }
 
    sum -= best;

    cout << fixed << setprecision(20) << (ld)sum/(ld)4 << ln;
    return 0;
}