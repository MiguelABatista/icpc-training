#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
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
const ll POTMAX = 32;

v64 pot2(POTMAX+2, 1);

ll pow(ll a, ll b, ll mod){
    if(b == 0) return 1;
    ll intermed = pow(a,b/2,mod);
    ll resp = (intermed*intermed)%mod;
    if(b%2 == 1) resp = (resp*a)%mod;
    return resp;
}
 
void solve(){
    ll a; cin >> a;

    ll b = 0;

    set<ll> resp;
    
    forn(k,1,POTMAX){
        ll a_pot_b_mod_2km1 = pow(a, b%pot2[k], pot2[k+1]);
        b = ((a % pot2[k+1] ) ^ a_pot_b_mod_2km1) % pot2[k+1];
    }

    if(pow(a,b, (1ll << (POTMAX))) == (a ^ b)){
        resp.insert(b);
    }

    forn(i,0,33){
        if(pow(a,i, (1ll << (POTMAX))) == (a ^ i)){
            resp.insert(i);
        }
    }

    if(pow(a,a, (1ll << (POTMAX))) == (a ^ a)){
        resp.insert(a);
    }

    cout << resp.size() << " ";
    for(ll x : resp) cout << x << " ";
    cout << ln;
}
int main(){
    _;
    forn(i,1,POTMAX+1){
        pot2[i] = pot2[i-1]*2;
    }

    ll t; cin >> t;
    while(t--) solve();

    return 0;
}