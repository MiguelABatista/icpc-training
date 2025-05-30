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
    ll n; cin >> n;
 
    v64 times(n);
    ll sum_d = 0;
    forn(i,0,n){
        ll t, d;
        cin >> t >> d;
        times[i] = t;
        sum_d += d;
    }
 
    sort(times.begin(), times.end());
 
    ll sum_t = 0;
    forn(i,0,n){
        sum_t += (n-i)*times[i];
    }
 
    cout << sum_d - sum_t << ln;
 
    return 0;
}