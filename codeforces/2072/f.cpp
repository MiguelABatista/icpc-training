#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

bool par(int n, int i) {
    while (i > 0) {
        if ((i & 1) == 1 && (n & 1) == 0) {
            return true;
        }
        i >>= 1;
        n >>= 1;
    }
    return false;
}

void solve(){
    ll n; ll k;
    cin >> n >> k;
    n--;
    forn(i,0,n+1){
        if(par(n,i)){
            cout << 0 << ' ';
        } else{
            cout << k << ' ';
        }
    }
    cout << ln;

}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}