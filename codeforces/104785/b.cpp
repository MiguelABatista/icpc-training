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

int main() {
    _;
    ll n, m, k; cin >> n >> m >> k;
    vector<v64> taps(m);
    forn(i, 0, k) {
        ll a, b; cin >> a >> b;
        taps[b-1].push_back(a);
    }

    forn(i, 0, m) {
        ll ans = 0;
        ll tot = taps[i].size();
        if (taps[i].size() % 2 == 1) {
            tot--;
            ans += 100;
        }
        for(ll j = 0; j < tot; j+=2) {
            ll temp = abs(taps[i][j] - taps[i][j+1]);
            if (temp == 0) temp = 100;
            ans += temp;
        }
        cout << ans << " ";
    }
    cout << ln;
    return 0;
}