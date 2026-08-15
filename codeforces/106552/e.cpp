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

const ll INF = 0x3f3f3f3f3f3f3f3fll;

const vector<pll> vis = {{0,0}, {1,0}, {-1,0}, {0,1}, {0,-1}};

bool conf(pll a, pll b){
    if(a.first == b.first){
        if(a.second - b.second == 1) return true; 
        if(a.second - b.second == 0) return true; 
        if(a.second - b.second == -1) return true; 
    }
    if(a.second == b.second){
        if(a.first - b.first == 1) return true; 
        if(a.first - b.first == 0) return true; 
        if(a.first - b.first == -1) return true; 
    }
    return false;
}

int main() {
    _;
    ll n, m, t; cin >> n >> m >> t;
    vector<vll> mat(n, vll(m));

    forn(i,0,n) forn(j,0,m) cin >> mat[i][j];

    vector<pll> posa(t);
    vector<pll> posb(t);
    forn(i,0,t){
        cin >> posa[i].first;
        cin >> posa[i].second;
        posa[i].first--;
        posa[i].second--;
    }
    forn(i,0,t){
        cin >> posb[i].first;
        cin >> posb[i].second;
        posb[i].first--;
        posb[i].second--;
    }

    ll ra = 0;
    ll rb = 0;

    forn(i,0,t){
        for(auto [tx, ty] : vis){
            pll drilla = {posa[i].first+tx, posa[i].second+ty};
            if(drilla.first < 0 || drilla.first >= n) continue;
            if(drilla.second < 0 || drilla.second >= m) continue;
            if(!conf(drilla, posb[i])){
                ra += mat[drilla.first][drilla.second];
                mat[drilla.first][drilla.second] = 0;
            }
        }
        for(auto [tx, ty] : vis){
            pll drillb = {posb[i].first+tx, posb[i].second+ty};
            if(drillb.first < 0 || drillb.first >= n) continue;
            if(drillb.second < 0 || drillb.second >= m) continue;
            if(!conf(drillb, posa[i])){
                rb += mat[drillb.first][drillb.second];
                mat[drillb.first][drillb.second] = 0;
            }
        }
    }

    cout << ra << " " << rb << ln;
    return 0;
}
