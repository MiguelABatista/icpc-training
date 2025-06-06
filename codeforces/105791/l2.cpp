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

ll f(ll x) {
    return x * (x + 1) * (x + 2);
}

ll bs(ll sup) {
    ll a = 0, b = min(sup, 1'000'000ll);
    ll x;
    while (a <= b) {
        x = (a + b) / 2;
        if (f(x) > sup) b = x - 1;
        else a = x + 1;
    }

    if (f(x) > sup) x--;
    return x;
}

void solve() {
    ll l, r; cin >> l >> r;
    ll xl = bs(l - 1), xr = bs(r);
    
    ll count = max((ll) 0, xr - xl);
    cout << count << ln;
}

int main(){
    ll tc = 1;
    cin >> tc;
    while (tc--) solve();
    return 0;
}