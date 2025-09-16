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
    ll n, d; cin >> n >> d;
    v64 v(n);
    forn(i, 0, n) cin >> v[i];
    ll a = -1, b = -1;
    forn (i, 0, n) {
        if (v[i] && a == -1) {
            a = i;
            continue;
        } else if (v[i] && b == -1) {
            b = i;
            continue;
        }
    }

    if (b == -1) {
        if (a == -1 || v[a] < d) {
            cout << "-1\n";
            return 0;
        } else {
            forn(i, 0, d) cout << a+1 << " \n"[i==d-1];
            return 0;
        }
    }
    
    forn(i, 0, d) cout << (i%2 == 0? a+1 : b+1) << " \n"[i==d-1];
    return 0;
}