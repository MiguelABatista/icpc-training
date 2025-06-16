#include <bits/stdc++.h>
using namespace std;

typedef __int128_t ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;
typedef complex<double> cd;

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
const int MAXD = 10000;
int main(){
    _;
    ll n; string s;
    cin >> s; n = s.size();

    ll sng = (s[0] == 'H' ? 1 : -1);

    vector<ll> roots;

    forn(i,0,n-1){
        if(s[i] != s[i+1]){
            roots.push_back(2*(i+1)+1);
        }
    }

    if(roots.empty()){
        cout << 0 << ln;
        cout << (long long)sng << ln;
        return 0;
    }

    vector<__int128_t> poly{1};      // degree 0, coefficient +1

    for (auto r : roots) {
        vector<__int128_t> nxt(poly.size() + 1);
        nxt.back() = poly.back();                     // coefficient of x^{d+1}  (still 1)

        for (size_t k = 1; k < nxt.size() - 1; ++k)   // k = 1..d
            nxt[k] = poly[k - 1] - r * poly[k];       // a_{k-1} − r·a_k

        nxt[0] = -r * poly[0];                        // constant term

        poly.swap(nxt);                   // constant term
    }

    bool should_flip = ((roots.size() & 1) ? (s[0]=='H') : (s[0]=='A'));
    if (should_flip)
        for (auto &x : poly) x = -x;


    cout << poly.size() - 1 << '\n';

    // coefficients from highest degree to constant term
    for (int i = (int)poly.size() - 1; i >= 0; --i) {
        cout << (long long)poly[i];       // each |coeff| < 2^63, fits in i64
        if (i) cout << ' ';               // space between numbers, none after last
    }
    cout << '\n';
    return 0;
}