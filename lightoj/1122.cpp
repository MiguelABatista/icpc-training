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

ll dp[11][10];
ll testcase = 1;

ll rec(ll size, ll curr, ll prevdig, set<ll> digits){
    if(curr == 0) return 1;

    if(dp[curr][prevdig] != -1) return dp[curr][prevdig];

    ll ans = 0;
    for(ll dig : digits){
        if(curr != size && abs(dig - prevdig) > 2) continue;
        ans += rec(size, curr-1, dig, digits);
    }

    dp[curr][prevdig] = ans;
    return ans;   
}

void solve(){
    ll m, n; cin >> m >> n;
    set<ll> digits;
    forn(i,0,m){
        ll aux; cin >> aux;
        digits.insert(aux);
    }

    memset(dp,-1,sizeof(dp));

    cout << "Case " << testcase++ << ": " << rec(n,n,0,digits) << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}