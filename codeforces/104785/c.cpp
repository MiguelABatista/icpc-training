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

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ld pi = 2*acos(0.0);

ll n, p;
vector<ld> pt;
vector<vector<vector<ld>>> area_map;

ld area(ll i, ll j, ll k){
    ld ang1 = pt[i]*pi/180;
    ld ang2 = pt[j]*pi/180;
    ld ang3 = pt[k]*pi/180;
    return (sin(ang2-ang1) + sin(ang3-ang2) + sin(ang1 - ang3))/2;
}

void prep(){
    area_map.resize(n, vector<vector<ld>>(n, vector<ld>(n)));
    forn(i, 0, n){
        forn(j, 0, n){
            forn(k, 0, n){
                area_map[i][j][k] = area(i, j, k);
            }
        }
    }
}

ld solve(ll st){
    // debug(st);
    vector<ld> best_curr(n), best_last(n, 0);
    best_last[0] = -INF;

    forn(x, 0, p-2){
        forn(i, 0, n){
            ld best = -INF;
            forn(j, 0, i){
                best = max(best, best_last[j] + area_map[st][(st+j)%n][(st+i)%n]);
            }
            best_curr[i] = best;
        }
        swap(best_curr, best_last);
        // debug(x);
        // for(auto x : best_last) cout << fixed << setprecision(10) << x << " ";
        // cout << ln << "------------------" << ln;
    }

    ld best = -INF;
    for(auto x : best_last) best = max(best, x);
    return best;
}

int main() {
    _; cin >> n >> p;
    pt.resize(n);
    forn(i, 0, n) cin >> pt[i];

    prep();

    ld best = 0;
    forn(i, 0, n){
        best = max(best, solve(i));
    }
    
    cout << fixed << setprecision(10) << best*1000000 << ln;

    return 0;
}