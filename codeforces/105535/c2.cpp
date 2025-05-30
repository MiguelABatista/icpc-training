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
const ll POTMAX = 32;

void solve(){
    _;
    ll a; cin >> a;

    ll pow2 = (1ll << POTMAX);
    ll ab = 1;
    forn(b, 0, pow2){
        if(ab == (a^b)){
            cout << 1 << " " << b << ln;
            return ;
        }
        ab = (ab*a) % pow2;
    }
    cout << 0 << ln;
    return ;
}
 
int main(){
    _;

    ll t; cin >> t;
    while(t--) solve();

    return 0;
}