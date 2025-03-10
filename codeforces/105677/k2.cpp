#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;
typedef vector<int> v32;
typedef vector<v32> vv32;
typedef vector<v64> vv64;
typedef vector<p64> vp64;

#define D_ false
#define F_ if(!D_)ios_base::sync_with_stdio(false), cin.tie(NULL)
#define P_ if(D_)cout<<"DEBUG\n"
#define dbg(x) if(D_) cout << #x << " = " << x << ln
#define forn(i, s, e) for(ll i = s; i < e; i++)
#define rforn(i, s, e) for(ll i = s; i > e; i--)
#define ln "\n"
#define dgb dbg
#define sq(x) ((x)*(x))

typedef double ld;
const ld DINF = 1e18;
const ld pi = acos(-1.0);
const ld eps = 1e-6;

bool eq(ld a, ld b) {
	return abs(a - b) <= eps;
}

struct pt { // ponto
	ld x, y;
	pt(ld x_ = 0, ld y_ = 0) : x(x_), y(y_) {}
	bool operator < (const pt p) const {
		if (!eq(x, p.x)) return x < p.x;
		if (!eq(y, p.y)) return y < p.y;
		return 0;
	}
	bool operator == (const pt p) const {
		return eq(x, p.x) and eq(y, p.y);
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

vector<pair<pt, ld>> circle;
vector<vector<ll>> graph;
vector<vector<pair<pt, ll>>> inter_point;
vector<bool> visited;
vector<ll> component;

map<pt, ll> retirados1;
map<pt, ll> retirados2;

ld angle(pt v){
    ld ang = atan2((ld)v.y, (ld)v.x);
    if(ang < 0) ang += 2*pi;
    return ang;
}

ld dist(pt p, pt q) { // distancia
	return hypot(p.y - q.y, p.x - q.x);
}

ld dist2(pt p, pt q) { // quadrado da distancia
	return sq(p.x - q.x) + sq(p.y - q.y);
}

pt rotate90(pt p) { // rotaciona 90 graus
	return pt(-p.y, p.x);
}

vector<pt> circ_inter(pt a, pt b, ld r, ld R) { // intersecao da circunf (a, r) e (b, R)
	vector<pt> ret;
	ld d = dist(a, b);
	if (d+eps > r+R or d+min(r, R) < max(r, R)+ eps) return ret;
	ld x = (d*d-R*R+r*r)/(2*d);
	ld y = sqrt(r*r-x*x);
	pt v = (b-a)/d;
	ret.push_back(a+v*x + rotate90(v)*y);
	if (y + eps > 0) ret.push_back(a+v*x - rotate90(v)*y);
	return ret;
}

ll check_inside(pt p){
    for(auto c : circle){
        if(dist2(p, c.first) + eps < sq(c.second)) return 1;
    }
    return 0;
}

void dfs(ll s){
    visited[s] = true;
    component.push_back(s);

    for(auto x : graph[s]){
        if(!visited[x]) dfs(x);
    }
}

pair<pt, ll> get_next(pt p, ll i){
    pt centro = circle[i].first;
    ld min_angle = 4*pi;
    ll next_ind = i;
    pt next_pt = p;

    for(auto x : inter_point[i]){
        ld curr_angle = angle(x.first - centro) - angle(p-centro);
        if(curr_angle < eps) curr_angle += 2*pi;

        if(curr_angle < min_angle){
            next_ind = x.second;
            next_pt = x.first;
            min_angle = curr_angle;
        }
    }

    return {next_pt, next_ind};
}

ll round_hull(){
    ll starting_pt, max_y=-2'000'000'000, points_in_border = 0;

    if(component.size() == 1){
        component.clear();
        return 0;
    }

    for(auto x : component){
        pt centro = circle[x].first;
        ld raio = circle[x].second;

        if(centro.y+raio > max_y){
            starting_pt=x;
            max_y = centro.y+raio;
        }
    }

    auto curr = get_next(circle[starting_pt].first + pt(0, circle[starting_pt].second), starting_pt);
    pt inicio_pt = curr.first;
    ll inicio_ind = curr.second;

    do{
        points_in_border++;
        retirados2[curr.first]++;
        curr = get_next(curr.first, curr.second);
    } while(!(curr.first == inicio_pt) || curr.second != inicio_ind);

    component.clear();
    return points_in_border;
}

int main(){
    F_; ll n; cin >> n;
    vector<pair<pt, ld>> circle_fake(n);
    graph.resize(n);
    inter_point.resize(n);
    visited.resize(n);

    forn(i, 0, n){
        cin >> circle_fake[i].first >> circle_fake[i].second;
    }

    forn(i, 0, n){
        bool circle_ruim = false;
        forn(j, 0, n){
            if(i == j) continue;
            
            if(circle_fake[j].second - circle_fake[i].second <= 0) continue;

            ll d2 = dist2(circle_fake[i].first, circle_fake[j].first);
            if( d2 < sq( circle_fake[j].second - circle_fake[i].second ) ) circle_ruim=true;
        }

        if(circle_ruim) continue;
        circle.push_back(circle_fake[i]);
    }

    n = circle.size();

    ll num_candidatos = 0;
    vector<pt> candidatos;

    forn(i, 0, n){
        forn(j, i+1, n){
            auto inter = circ_inter(circle[i].first, circle[j].first, circle[i].second, circle[j].second);
            if(inter.empty()) continue;
            graph[i].push_back(j);
            graph[j].push_back(i);

            num_candidatos += inter.size();
            assert(inter.size() == 2);

            for(auto p : inter){
                inter_point[i].push_back({p, j});
                inter_point[j].push_back({p, i});
                candidatos.push_back(p);
            }
        }
    }

    for(auto p : candidatos){
        if(check_inside(p) == 0) continue;
        num_candidatos -= check_inside(p);
        retirados1[p]++;
    }

    forn(i, 0, n){
        if(visited[i]) continue;
        dfs(i);
        num_candidatos -= round_hull();
    }

    if(num_candidatos <= 0){
        cout << 0 << ln;
        return 0;
    }
    
    for(auto x : candidatos){
        assert(retirados1[x] < 2);
        assert(retirados2[x] < 2);
    }

    cout << 1 << ln;
    P_; return 0;
}
