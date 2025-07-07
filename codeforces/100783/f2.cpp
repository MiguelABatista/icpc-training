#include <bits/stdc++.h>
using namespace std;


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

bool intersect_interval(ll x1, ll y1, ll x2, ll y2){
    if(y1 < x2 or y2 < x1) return false;
    return true;
}

bool intersect_rect(ll x1, ll y1, ll w1, ll h1, ll x2, ll y2, ll w2, ll h2){
    if(x1 == x2 + w2){
        return intersect_interval(y1, y1+h1, y2, y2+h2);
    }
    if(x2 == x1 + w1){
        return intersect_interval(y1, y1+h1, y2, y2+h2);
    }
    if(y1 == y2 + h2){
        return intersect_interval(x1, x1+w1, x2, x2+w2);
    }
    if(y2 == y1 + h1){
        return intersect_interval(x1, x1+w1, x2, x2+w2);
    }
    return false;
}

int main() {
    _;
    ll n; cin >> n;
    v64 areas(n), x(n), y(n), w(n), h(n);
    dsu sdu(n);
    
    forn(i, 0, n) {
        cin >> x[i] >> y[i] >> w[i] >> h[i];
        areas[i] = w[i]*h[i];
        forn(j, 0, i){
            if(intersect_rect(x[i], y[i], w[i], h[i], x[j], y[j], w[j], h[j])) sdu.uni(i, j);
        }
    }

    forn(i, 0, n) {
        if (sdu.find(i) == i) continue;
        areas[sdu.find(i)] += areas[i];
    }

    cout << *max_element(areas.begin(), areas.end()) << ln;

    return 0;
}