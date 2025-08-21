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

void solve(){
    ll a, b, k;
    cin  >> a >> b >> k;
    ll d = gcd(a,b);
    ll ax = a/d;
    ll bx = b/d;
    if(ax <= k && bx <= k){
        cout << 1 << ln;
        return;
    }
    cout << 2 << ln;
    // a = alpha*t
    // b = beta*t
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}