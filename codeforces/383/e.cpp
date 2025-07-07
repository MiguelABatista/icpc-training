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
const ll pot2 = 16'777'216;

ll convert(string s){
    ll ans = 0;
    for(char c: s){
        ll aux = (1 << (c-'a'));
        if(!(ans & aux)) ans+= aux;
    }
    return ans;
}

int main(){
    _;
    ll n; cin >> n;

    v64 dp(pot2, 0);

    forn(i,0,n){
        string s; cin >> s;
        ll aux = convert(s);
        dp[aux]++;
    }

    forn(i,0,24){
        ll aux = (1<<i);
        forn(mask, 0, pot2){
            if((mask & aux)){
                dp[mask] += dp[mask^aux];
            }
        }
    }

    ll ans = 0;

    forn(i,0,pot2){
        ans = (ans^((n-dp[i])*(n-dp[i])));
    }

    cout << ans << ln;
    return 0;
}