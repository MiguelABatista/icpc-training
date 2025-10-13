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
    ll tot = n * m;
    v64 pts(tot);
    v64 linhas(n), cols(m);
    forn(i, 0, tot) cin >> pts[i], pts[i]--;

    forn(i, 0, tot) {
        ll x = pts[i]/m;
        ll y = pts[i]%m;        
        linhas[x]++;
        cols[y]++;
        
        // debug(m);
        // debug(x);
        // debug(y);
        // forn(j, 0, n) cout << linhas[j] << " \n"[j==n-1];
        // // forn(j, 0, m) cout << cols[j] << " \n"[j==m-1];

        if (linhas[x] >= m-k && i >= m-1) {
            cout << i+1 << ln;
            return;
        }
        // if (cols[y] >= n-k && i >= n) {
        //     cout << "c: " << i << ln;
        //     return;
        // }
    } 
}

int main() {
    _;
    ll t; cin >> t;
    while (t--) solve();
    return 0;
}
