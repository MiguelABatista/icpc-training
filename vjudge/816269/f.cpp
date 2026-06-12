#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MOD = 1'000'000'007;

int main() {
    _;
    ll n;
    cin >> n;
    vector<vll> dp(n,vll(n));
    
    vector<string> s(n);

    forn(i,0,n){
        cin >> s[i];
    }

    dp[0][0] = (s[0][0] == '.');
    
    forn(i,0,n){
        forn(j,0,n){
            if(s[i][j] == '*') continue;
            dp[i][j] = (dp[i][j] + (i == 0 ? 0 : dp[i-1][j]) + (j == 0 ? 0 : dp[i][j-1]))%MOD;
        }   
    }
    // forn(i,0,n){
    //     forn(j,0,n){
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << ln;
    // }
    cout <<  dp[n-1][n-1] << ln ;
    return 0;
}
