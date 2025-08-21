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
    ll n, m; cin >> n >> m;
    ll sum = 0, best1 = INF, best2 = INF;
    forn(i, 0, n){
        forn(j, 0, m){
            ll a; cin >> a;
            sum += a;
            if((i+j)%2 == 0) best1 = min(best1, a);
            else best2 = min(best2, a);
        }
    }

    if(m%2 == 0 and n%2 == 0){
        // cout << sum - best1 << ln;
        cout << sum - best2 << ln;
        return 0;
    }

    cout << sum << ln;

    return 0;
}