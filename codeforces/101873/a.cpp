#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
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
const ll OFFSETX = 1000;
const ll OFFSETY = 1000;
const ll MAXX =  2000;
const ll MAXY =  2000;

int main(){
    _; ll n; cin >> n;

    vector<set<ll>> verde(MAXY+1), vermelho(MAXY+1);
    forn(i, 0, n){
        ll c, x, y; cin >> x >> y >> c;
        x += OFFSETX;
        y += OFFSETY;

        if(c == 1){
            verde[y].insert(x);
        }
        if(c == 2){
            vermelho[y].insert(x);
        }
    }

    vector<pair<ld, ld>> pverde;

    pverde.push_back({MAXX+2, MAXY+1});
    pverde.push_back({MAXX+1, MAXY+1});
    for(ll y = MAXY; y >= 0; y--){
        if(verde[y].empty()) continue;

        pverde.push_back({MAXX+1, y + 0.4});
        pverde.push_back({-0.8, y + 0.4});
        pverde.push_back({-0.8, y + 0.2});

        for(auto x : verde[y]){
            pverde.push_back({x - 0.2, y + 0.2});
            pverde.push_back({x - 0.2, y - 0.1});
            pverde.push_back({x + 0.2, y - 0.1});
            pverde.push_back({x + 0.2, y + 0.2});
        }

        pverde.push_back({MAXX+1, y+0.2});
    }
    pverde.push_back({MAXX+1, -1});
    pverde.push_back({MAXX+2, -1});

    vector<pair<ld, ld>> pvermelho;

    pvermelho.push_back({-2, MAXY+1});
    pvermelho.push_back({-1, MAXY+1});
    for(ll y = MAXY; y >= 0; y--){
        if(vermelho[y].empty()) continue;

        pvermelho.push_back({-1, y - 0.2});

        for(auto x : vermelho[y]){
            pvermelho.push_back({x-0.2, y-0.2});
            pvermelho.push_back({x-0.2, y+0.1});
            pvermelho.push_back({x+0.2, y+0.1});
            pvermelho.push_back({x+0.2, y-0.2});
        }

        pvermelho.push_back({MAXX + 0.8, y - 0.2});
        pvermelho.push_back({MAXX + 0.8, y - 0.4});
        pvermelho.push_back({-1, y - 0.4});
    }
    
    cout << sz(pverde) << ln;
    for(auto& p: pverde){
        cout << fixed << setprecision(5) << p.first-OFFSETX << " " << p.second-OFFSETY << ln;
    }

    cout << sz(pvermelho) << ln;
    for(auto& p: pvermelho){
        cout << fixed << setprecision(5) << p.first-OFFSETX << " " << p.second-OFFSETY << ln;
    }

    return 0;
}