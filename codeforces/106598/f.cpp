#include <bits/stdc++.h>
using namespace std;



typedef long long ll;
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
#define debugm(v) trace(cout << __LINE__ << ": " #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

struct TJ {
    ll n, timer = 0;
    vector<vll>& gg;
    vll tin, low;

    vector<pll> briges;

    TJ(ll n_, vector<vll>& g_): n(n_), gg(g_){
        tin.assign(n,-1);
        low.resize(n);
        forn(i,0,n) if(tin[i] == -1) dfs(i);
    }

    void dfs(ll v, ll p = -1){
        tin[v] = low[v] = timer++;
        ll ch = 0;

        for(ll to:gg[v]){
            if(to ==p) continue;

            if(tin[to] == -1){
                
                dfs(to, v);
                low[v] = min(low[v], low[to]);

                if(low[to] > tin[v]) briges.push_back({v,to});

                ch++;
            }else{
                low[v] = min(low[v], tin[to]);
            }
        }
    }
};

struct dsu {
    vll id, len;

    dsu(ll n) : id(n), len(n,1) { iota(id.begin(), id.end(), 0);}

    ll find(ll a) { return a == id[a] ? a : id[a] = find(id[a]);}

    bool uni(ll a, ll b){
        a = find(a), b = find(b);
        if(a == b) return false;
        if (len[a] < len[b]) swap(a,b);
        len[a] += len[b], id[b] = a;
        return true;
    }
};

struct pt{
    ll x, y;
    pt(ll x_ = 0, ll y_ = 0) : x(x_), y(y_) {}
    bool operator < (const pt p) const {
        if(x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator == (const pt p) const {
        return x == p.x && y == p.y;
    }
    pt operator + (const pt p) const { return pt(x + p.x, y + p.y); }
    pt operator - (const pt p) const { return pt(x - p.x, y - p.y); }
    pt operator * (const ll c) const { return pt(x*c, y*c); }
    ll operator * (const pt p) const { return x*(ll)p.x + y*(ll)p.y; }
    ll operator ^ (const pt p) const { return x*(ll)p.y - y*(ll)p.x; }
    friend istream& operator >> (istream& in, pt& p) {
        return in >> p.x >> p.y;
    }
};

ll sarea2(pt p, pt q, pt r) {
    return (q-p)^(r-q);
}

bool ccw(pt p, pt q, pt r, bool strict = true) {
    return sarea2(p,q,r) > 0 || (!strict && sarea2(p,q,r) == 0);
}

int quad(pt p) {
    return (p.x < 0)^3*(p.y<0);
}

bool compare_angle(pt p, pt q) {
    if(quad(p) !=  quad(q)) return quad(p) < quad(q);
    return ccw(q, pt(0,0), p);
}

struct line {
    pt p, q;
    line(pt p_, pt q_) : p(p_), q(q_) {}
};

bool isinseg(pt p, line r){
    pt a = r.p - p, b = r.q - p;
    return (a^b) == 0 && (a*b) <= 0;
}

bool inpolygon(vector<pt> &p, pt a, bool strict = true) {
    ll cnt = 0, n = sz(p);
    forn(i, 0, n) {
        pt q = p[(i+1)%n];
        if(isinseg(a, line(p[i], q))) return !strict;
        cnt ^= (((a.y < p[i].y) - (a.y < q.y))*((p[i]-a)^(q-a))) > 0;
    }
    return cnt;
}

vector<vll> g;
vector<pt> pessoas;
vector<pt> colunas;
map<pt,ll> name;
vector<bool> resposta;

void func(vll& comp){
    if(sz(comp) < 2) return;

    debugv(comp);

    vector<pt> ord;
    forn(i, 0, sz(comp)) ord.push_back(colunas[comp[i]]);
    sort(ord.begin(), ord.end());

    vector<pt> poly;
 
    pt curr = *ord.begin(), dir(-1, 0);
    ll ind = name[curr];
    set<pll> added;

    while(true){
        poly.push_back(curr);
        vector<pt> adj;
        for(auto i : g[ind]) adj.push_back(colunas[i] - colunas[ind]);
        sort(adj.begin(), adj.end(), compare_angle);

        trace(
            cout << "adj" << ln;
            forn(i, 0, sz(adj)) cout << adj[i].x << ":" << adj[i].y << " ";
            cout << ln;
        )   
        
        bool found = false;
        for(auto p : adj) {
            if(compare_angle(dir, p)) {
                dir = p;
                found = true;
                break;
            }
        }
        if(!found) dir = adj[0];

        trace(
            cout << curr.x << " " << curr.y << ln;
            cout << dir.x << " " << dir.y << ln;
        )

        curr = curr + dir;
        if(added.count({ind, name[curr]})) break;
        added.insert({ind, name[curr]});
        dir = dir*(-1);
        ind = name[curr];
    }

    trace(
        cout << "poly" << ln;
        forn(i, 0, sz(poly)) cout << poly[i].x << ":" << poly[i].y << " ";
        cout << ln;
    )

    forn(i, 0, sz(resposta)) resposta[i] =  (resposta[i]|inpolygon(poly, pessoas[i]));
}

int main() {
    _;
    ll n, m; cin >> n >> m;
    colunas.resize(n);
    vector<pll> edges;
    vector<pll> ned(m);
    vector<vll> gg(n);
    vector<vll> comps(n);

    dsu sdu(n);
    g.resize(n);

    forn(i,0,n){
        ll x, y; cin >> x >> y;
        colunas[i] = {x,y};
        name[colunas[i]] = i;
    }

    forn(i,0,m){
        ll a, b;
        cin >> a >> b;
        a--, b--;
        edges.push_back({a,b});
        gg[a].push_back(b);
        gg[b].push_back(a);
    }
    
    ll k; cin >> k;
    pessoas.resize(k);
    resposta.resize(k);
    
    forn(i,0,k){
        ll x, y; cin >> x >> y;
        pessoas[i] = {x,y};
    }
    
    TJ tj(n, gg);
    set<pll> isbri;
    
    for(auto [a,b] : tj.briges){
        isbri.insert({a,b});
        isbri.insert({b,a});
    }
    
    for(auto [a,b] : edges){
        if(isbri.find({a,b}) != isbri.end()) continue;
        ned.push_back({a,b});
        sdu.uni(a,b);
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // forn(i,0,n) {debugv(g[i]);}

    edges = ned;
    m = sz(edges);
    comps.resize(n);

    forn(i,0,n) comps[sdu.find(i)].push_back(i);

    forn(i,0,n) func(comps[i]);

    string gaba = "GP";

    forn(i, 0, k) cout << gaba[resposta[i]]; 
    cout << ln;
    

    return 0;
}