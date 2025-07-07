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
const ll pot2 = 262'144;
const ll lim = 18;

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

int main(){
    _;  
    v64 pot(pot2, 1);
    forn(i,1,pot2){
        pot[i] = sum(pot[i-1], pot[i-1]);
    }
    
    ll n; cin >> n;
    v64 vec(n);
    v64 dp(pot2, 0);
    v64 resp(pot2, 0);

    forn(i,0,n){
        cin >> vec[i];
        dp[vec[i]]++;
    }
    forn(i,0,lim){
        ll aux = (1<<i);
        forn(mask, 0, pot2){
            if(!(mask & aux)){
                dp[mask] += dp[mask^aux];
            }
        }
    }

    // forn(i,0,10) cout << dp[i] << " \n"[i==9];
    
    forn(mask, 0, pot2) resp[mask] = sub(pot[dp[mask]],1);
    
    forn(i,0,lim){
        ll aux = (1<<i);
        for(ll mask = pot2-1; mask >= 0; mask--){
            if(!(mask & aux)){
                resp[mask] = sub(resp[mask], resp[mask^aux]);
            }
        }
    }

    forn(i,0,n+1) cout << resp[i] << " \n"[i==n];
    return 0;
}