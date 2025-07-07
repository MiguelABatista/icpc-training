#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef long long ll;
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

struct prod {
    ld rank;
    ll id;
    ll cA, cB;
    ld needed;
    bool sideA;
    bool operator <(const prod o) const {
        if (rank != o.rank) {
            return rank < o.rank;
        }
        return id < o.id;
    }
};

int main(){
    _;
    ll n; cin >> n;
    vector<prod> v(n);
    ld pa = 0, pb = 0;
    forn(i, 0, n) {
        ll a, u, b, w; cin >> a >> u >> b >> w;
        v[i].id = i;
        v[i].cA = a;
        v[i].cB = b;
        v[i].needed = u + w;
        pa += a*u;
        pb += b*w;
        if (a < b) {
            v[i].sideA = true;
            v[i].rank = (ld) a / (ld) b;
        } else {
            v[i].sideA = false;
            v[i].rank = (ld) b / (ld) a;
        }
    }
    sort(v.begin(), v.end());
    ld tot = pa + pb;
    forn(i, 0, n) {
        if (v[i].sideA) {
            if (pa / v[i].cA >= v[i].needed) {
                pa -= v[i].cA * v[i].needed;
                continue;
            }
            v[i].needed -= pa / v[i].cA;
            pa = 0;

            pb -= v[i].cB * v[i].needed;
        } else {
            if (pb / v[i].cB >= v[i].needed) {
                pb -= v[i].cB * v[i].needed;
                continue;
            }
            v[i].needed -= pb / v[i].cB;
            pb = 0;

            pa -= v[i].cA * v[i].needed;
        }

    }

    cout << fixed << setprecision(20) << tot - (pa+pb) << ln;


    return 0;
}