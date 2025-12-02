#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n; cin >> n;
    if(n == 1){
        cout << 1 << ln;
        return;
    }
    if(n == 2){
        cout << 9 << ln;
        return;
    }
    ll val1 = n*n + n*n-1 + n*n-n;
    ll val2 = n*n-2 + n*n-1 + n*n + n*n-1-n;
    ll val3 = n*n-n-1 + n*n-n-1+1 + n*n-n-1-1 + n*n-n-1+n + n*n-n-1-n;
    // cout << val1 << " " << val2 << " " << val3 << ln;
    cout << max(val1, max(val2, val3)) << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}