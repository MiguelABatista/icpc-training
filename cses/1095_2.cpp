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

const ll MOD = 1'000'000'007;

inline ll sum(ll a, ll b) { a += b; if (a >= MOD) a -= MOD; return a; }
inline ll sub(ll a, ll b) { a -= b; if (a < 0)  a += MOD; return a; }
inline ll mult(ll a, ll b) { return (a * b) % MOD; }

inline ll pot(ll base, ll exp) {
    if(exp == 0) return 1;

    ll resp = pot(base, exp/2);
    resp = mult(resp, resp);
    if(exp&1) resp = mult(resp, base);
    return resp;
}

inline ll inv_mod(ll a) {return pot(a, MOD-2);}


const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _;
    ll n;
    cin >> n;
    forn(i,0,n){
        ll a, b; cin >> a >> b;

        cout << pot(a,b) << ln;
    }
    return 0;
}