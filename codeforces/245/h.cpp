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

int main(){
    _;
    string s; cin >> s;
    ll n = sz(s);
    ll q; cin >> q;
    vector<v64> dp(n, v64(n));
    vector<vector<bool>> ispal(n, vector<bool>(n, false));

    forn(i,0,n){
        ispal[i][i] = true;
        dp[i][i] = 1;
    }
    
    forn(i,0,n-1){
        ispal[i][i+1] = s[i] == s[i+1];
        dp[i][i+1] = 2+ispal[i][i+1];
    }

    forn(t,2,n){
        forn(i,0,n-t){
            ll j = i+t;
            ispal[i][j] = (s[i] == s[j])&&(ispal[i+1][j-1]);
            dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1] + ispal[i][j];
        }
    }

    forn(i,0,n) debugv(ispal[i]);
    forn(i,0,n) debugv(dp[i]);
    while(q--){
        ll a, b; cin >> a >> b;
        a--, b--;
        cout << dp[a][b] << ln;
    }
    return 0;
}