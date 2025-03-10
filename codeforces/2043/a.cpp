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
map<ll,ll> resp;



ll dp(ll n){
    ll ans;
    if(resp.find(n) != resp.end()) ans = resp[n];
    else ans = 2*dp(n/4); 
    
    resp[n] == ans; 
    return ans;
}

void solve(){
    ll n; cin >> n;
    resp.clear();
    resp[1] = 1;
    resp[2] = 1;
    resp[3] = 1;
    cout << dp(n) << ln;
}

int main(){
    _;
    ll t; cin >> t;

    while(t--) solve();

    return 0;
}