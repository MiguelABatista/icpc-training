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

int main(){
    _;
    ll n;
    cin >> n;
    v64 a(n),b(n),c(n);

    forn(i,0,n) cin >> a[i] >> b[i] >> c[i];

    v64 dpa(n,0), dpb(n,0), dpc(n,0);

    dpa[0] = a[0];
    dpb[0] = b[0];
    dpc[0] = c[0];

    forn(i,1,n){
        dpa[i] = a[i] + max(dpb[i-1], dpc[i-1]);
        dpb[i] = b[i] + max(dpa[i-1], dpc[i-1]);
        dpc[i] = c[i] + max(dpa[i-1], dpb[i-1]);
    }

    // cout << dpa[n-1] << ln;
    // cout << dpb[n-1] << ln;
    // cout << dpc[n-1] << ln;

    cout << max({dpa[n-1], dpb[n-1], dpc[n-1]}) << ln;
    return 0;
}