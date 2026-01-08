#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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


int main(){
    _;
    double a, b, c;
    ll cx, cy;
    cin >> a >> b >> c;
    cin >> cx >> cy;

    vector<double> x(3);
    vector<double> y(3);

    x[0] = -1/a;
    y[0] = c/(2*a);

    x[1] = 1/b;
    y[1] = c/(2*b);

    x[2] = 0;
    y[2] = -1;

    double l1, l2, l3;
    
    l1 = sqrt((x[0]-x[1])*(x[0]-x[1])+(y[0]-y[1])*(y[0]-y[1]));
    l2 = sqrt((x[0]-x[2])*(x[0]-x[2])+(y[0]-y[2])*(y[0]-y[2]));
    l3 = sqrt((x[2]-x[1])*(x[2]-x[1])+(y[2]-y[1])*(y[2]-y[1]));

    double lmin = min({l1,l2,l3});
    ll mult = ll(floor(1/lmin)+0.5) + 1;

    forn(i,0,3){
        cout << fixed << setprecision(20) << mult*x[i] + cx << " " << mult*y[i] + cy << ln; 
    }
    return 0;
}