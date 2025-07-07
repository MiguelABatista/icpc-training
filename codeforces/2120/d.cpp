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

const ll MOD = 1'000'000'007;

inline ll sum(ll a, ll b) { a += b; if (a >= MOD) a -= MOD; return a; }
inline ll sub(ll a, ll b) { a -= b; if (a < 0)  a += MOD; return a; }
inline ll mult(ll a, ll b) { return (a * b) % MOD; }

inline ll pot(ll base, ll exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = mult(res, base);
        base = mult(base, base);
        exp >>= 1;
    }
    return res;
}

inline ll inv_mod(ll a) {return pot(a, MOD-2);}

void solve(){
    ll a, b, k;
    cin >> a >> b >> k;
    ll n = sum(mult(a-1,k), 1);

    ll num = 1;
    ll dem = 1;

    forn(i,0,a){
        num = mult(num, (n-i));
        dem = mult(dem, i+1);
    }

    ll m = mult(num, inv_mod(dem));
    m = mult(m, b-1);
    m = mult(m, k);
    m = sum(m, 1);
    cout << n << " " << m << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}