#include <bits/stdc++.h>
using namespace std;
 #pragma GCC optimize("O3,unroll-loops,fast-math")
 
typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ 42
    #define debug(x) cout << __LINE__ << ": "<< #x << " = " << x << ln;
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) 42
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

struct dsu {
    vector<ll> id, sz;

    dsu(ll n) : id(n), sz(n, 1) { iota(id.begin(), id.end(), 0); }

    ll find(ll a) {return a == id[a] ? a : id[a] = find(id[a]); }

    void uni(ll a, ll b) {
        a = find(a), b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        sz[a] += sz[b], id[b] = a;
    }
};

inline ll getaa(vector<ll>& s, ll i){
    for(ll x: s) if(x != i) return x;
    return -1;
}

int main() {
    _;
    ll n; cin >> n;
    // map<ll, set<ll>> dx, dy;
    // map<p64, vector<ll>> poli;
    vector<set<ll>> dx(10'100), dy(10'100);
    vector<map<ll,v64>> poli(10100);
    
    v64 areas(n);
    dsu sdu(n);
    v64 xorig(n), yorig(n), worig(n), horig(n);
    v64 xworig(n), yhorig(n);

    set<ll> compx, compy;
    forn(i, 0, n) {
        ll x, y, w, h; cin >> x >> y >> w >> h;
        areas[i] = w*h;
        xorig[i] = x; yorig[i] = y; worig[i] = w; horig[i] = h;
        xworig[i] = xorig[i]+worig[i];
        yhorig[i] = yorig[i]+horig[i];

        compx.insert(x);
        compx.insert(x+w);
        compy.insert(y);
        compy.insert(y+h);
    }

    map<ll ,ll> tradx;
    map<ll ,ll> trady;
    
    ll aux = 0;
    for(ll val : compx){
        tradx[val] = aux++;
    }

    aux = 0;
    for(ll val : compy){
        trady[val] = aux++;
    }

    v64 x_(n), y_(n), xw_(n), yh_(n);

    forn(i,0,n){
        x_[i] = tradx[xorig[i]];
        xw_[i] = tradx[xworig[i]];
        y_[i] = trady[yorig[i]];
        yh_[i] = trady[yhorig[i]];
    }

    forn(i, 0, n) {
        ll x, y, xw, yh;
        x = x_[i];
        xw = xw_[i];
        y = y_[i];
        yh = yh_[i];

        dx[x].insert(y);
        dx[x].insert(yh);
        dx[xw].insert(y);
        dx[xw].insert(yh);

        dy[y].insert(x);
        dy[y].insert(xw);
        dy[yh].insert(x);
        dy[yh].insert(xw);

        poli[x][y].push_back(i);
        poli[xw][y].push_back(i);
        poli[x][yh].push_back(i);
        poli[xw][yh].push_back(i);
    }

    forn(i, 0, n) {
        ll x, y, xw, yh;
        x = x_[i];
        xw = xw_[i];
        y = y_[i];
        yh = yh_[i];


        for (auto ox = dy[y].lower_bound(x); ox != dy[y].end() && ox != dy[y].lower_bound(xw+1); ox++) {
            ll temp = getaa(poli[*ox][y],i);
            if(temp == -1) continue;
            sdu.uni(temp, i);
        }
        for (auto ox = dy[yh].lower_bound(x); ox != dy[yh].end() && ox != dy[yh].lower_bound(xw+1); ox++) {
            ll temp = getaa(poli[*ox][yh],i);
            if(temp == -1) continue;
            sdu.uni(temp, i);
        }
        for (auto oy = dx[x].lower_bound(y); oy != dx[x].end() && oy != dx[x].lower_bound(yh+1); oy++) {
            ll temp = getaa(poli[x][*oy],i);
            if(temp == -1) continue;
            sdu.uni(temp, i);
        }
        for (auto oy = dx[xw].lower_bound(y); oy != dx[xw].end() && oy != dx[xw].lower_bound(yh+1); oy++) {
            ll temp  = getaa(poli[xw][*oy],i);
            if(temp == -1) continue;
            sdu.uni(temp, i);
        }
    }

    forn(i, 0, n) {
        if (sdu.find(i) == i) continue;
        areas[sdu.find(i)] += areas[i];
    }

    cout << *max_element(areas.begin(), areas.end()) << ln;

    return 0;
}