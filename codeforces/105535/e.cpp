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

ll pow(ll a, ll b, ll mod){
    if(b == 0) return 1;
    ll intermed = pow(a,b/2,mod);
    ll resp = (intermed*intermed)%mod;
    if(b%2 == 1) resp = (resp*a)%mod;
    return resp;
}

int main(){
    _;
    ll resp = 2699537706;
    cout << bitset<32>(resp) << ln;

    cout << (pow(3,resp,(1ll<<32)) == (3^resp)) << ln;
    return 0;
}