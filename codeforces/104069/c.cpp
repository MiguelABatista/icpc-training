#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"
#define coutp cout << setprecision(15) << fixed

#if defined(DEBUG) || defined(debug)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _; ld x, y; cin >> x >> y;
    ld vb, vc; cin >> vb >> vc;
    ld ra = max(sqrt(x*x/4 + y*y), (ld)x);
    
    // coutp << x*x/4 << ln;
    // coutp << y*y << ln;
    // coutp << x*x/4 + y*y << ln;

    coutp << vb*ra/(2*x-ra) << ln;
    return 0;
}