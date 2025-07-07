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
const ll pot2 = 4'194'304;

int main(){
    _;
    ll n; cin >> n;
    v64 vec(n);
    v64 dp(pot2, -1);

    forn(i,0,n){
        cin >> vec[i];
        dp[vec[i]] = i;
    }

    forn(i,0,22){
        forn(mask,0,pot2){
            if(mask&(1<<i)){
                dp[mask] = max(dp[mask], dp[mask^(1<<i)]);
            }
        }
    }

    forn(i,0,n) cout << ((dp[(pot2-1)^vec[i]]== -1) ? -1 : vec[dp[(pot2-1)^vec[i]]]) << " \n"[i == n-1];
    return 0;
}