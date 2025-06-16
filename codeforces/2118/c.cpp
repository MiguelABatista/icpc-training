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

ll highest_bit(ll x) {
    if (x == 0) return 0;
    return 1LL << (63 - __builtin_clzll(x));
}

// Conta o número de bits 1 em x
ll count_ones(ll x) {
    return __builtin_popcountll(x);
}

void solve(){
    ll n, k; cin >> n >> k;
    
    v64 a(n);
    forn(i,0,n) cin >> a[i];
    debug(1);
    ll pot2 = 1;
    ll b = 0;

    forn(i,0,n) b += count_ones(a[i]);

    while(k > 0){
        if(k < pot2) break;

        debug(k);
        forn(i,0,n){ 
            if((a[i] & 1) == 0){
                if(k < pot2) break;
                k -= pot2;
                b++;
            } 
            a[i] /= 2;
        } 
        pot2 *= 2;
    }
    cout << b << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}