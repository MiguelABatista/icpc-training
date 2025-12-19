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
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];
    vector<bool> dp(n);
    dp[n-1] = false;
    if(n-1 - vec[n-1] >= 0) dp[n-1 - vec[n-1]] = true;
    for(ll i = n-2; i>= 0; i--){
        debugv(dp);

        ll val = vec[i];
        if(val+i == n-1) dp[i] = true;
        if(val+i <= n-2){
            if(dp[i+val+1]) dp[i] = true;
        }
        if(i-val >= 0 && dp[i+1]) dp[i-val] = true;
    }   
    debugv(dp);

    if(dp[0]) cout << "YES" << ln;
    else cout << "NO" << ln;
    // cout << dp[0] << ln;
    trace(cout << "-----------\n\n";);
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}