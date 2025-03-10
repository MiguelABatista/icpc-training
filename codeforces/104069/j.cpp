#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _;
    ll n; cin >> n;
    v64 sum(n+1), smallest(n+1, INF), biggest(n+1, -1);
    forn(i, 1, n+1) {
        ll t, v; cin >> t >> v;
        sum[i] = sum[i-1];
        smallest[i] = smallest[i-1];
        biggest[i] = biggest[i-1];

        if (t == 1) {
            sum[i] += v;
            smallest[i] = min(smallest[i-1], v);
            biggest[i] = max(biggest[i-1], v);
        } else if (t == 2) {
            cout << biggest[v] << ln;
        } else if (t == 3) {
            cout << smallest[v] << ln;
        }else if (t == 4) {
            cout << sum[v] << ln;
        }
    }

    return 0;
}