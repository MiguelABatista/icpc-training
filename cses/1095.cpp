// pot 2,  on
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

 ll sum(ll a, ll b) { a += b; if (a >= MOD) a -= MOD; return a; }
 ll sub(ll a, ll b) { a -= b; if (a < 0)  a += MOD; return a; }
 ll mult(ll a, ll b) { return (a * b) % MOD; }

 ll pot(ll a, ll b){
    ll expo=1, prod=a;

    while(b>=1){
        if(b%2 == 1) expo = mult(expo,prod);
        prod = mult(prod,prod);
        b = b/2;
    }
    
    return expo;
}

 ll pot2(ll base, ll exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = mult(res, base);
        base = mult(base, base);
        exp >>= 1;
    }
    return res;
}

 ll inv_mod(ll a) {return pot(a, MOD-2);}


int main(){
    _;
    ll n; cin >> n;
    forn(i,0,n){
        ll a, b;
        cin >> a >> b;
        cout << pot2(a,b) << ln;
    }
    return 0;
}