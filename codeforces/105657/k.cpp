#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void) 0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve() {
    ll n, m, k; cin >> n >> m >> k;
    v64 linha(n, 0);
    ll ans = -1;
    forn(x,0,m*n){
        ll a; cin >> a;
        a--;
        // ll j = a%m;
        ll i = a/m;
        linha[i]++;
        if(ans == -1 && linha[i] == m-k){
            ans = x+1;
        }
    }
    cout << max(ans, m) << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while (t--) solve();
    return 0;
}
