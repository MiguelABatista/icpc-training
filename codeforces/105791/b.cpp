#include <bits/stdc++.h>
using namespace std;

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

struct point {
    ll x, y;
};

double hypot(point a, point b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}
int main(){
    ll n, k; cin >> n >> k;
    point a, b;
    double dist = 0;
    double maxHeight = 0;
    cin >> b.x >> b.y;

    forn (i, 0, n - 1) {
        if (dist >= k) break;
        a = b;
        cin >> b.x >> b.y;
        maxHeight = max(maxHeight, (double)a.y);
        dist += hypot(a, b);
    }
    if (dist < k) {
        maxHeight = max(maxHeight, (double)b.y);
    } else {
        double d0 = hypot(a, b);
        double d1 = dist - k;
        double dy0 = b.y - a.y;
        double dy1 = d1 * dy0 / d0;
        double h = b.y - dy1;
        maxHeight = max(maxHeight, h);
    }
    cout << setprecision(30) << maxHeight << ln;
    return 0;
}