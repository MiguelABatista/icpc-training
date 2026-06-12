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
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MAX = 256;

int main() {
    _;
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n){
        string s; cin >> s;
        vec[i] = stoi(s, 0, 16);
    }

    vector<vector<pll>> dp(n, vector<pll>(MAX, {-INF, 0}));

    dp[0][0] = {0,0};
    dp[0][1] = {vec[0]^0,0};

    forn(i,1,n){
        dp[i][0] = dp[i-1][0];
        if(dp[i][0].first < dp[i-1][MAX-1].first + dp[i-1][MAX-1].second*MAX + (vec[i]^(MAX-1))){
            dp[i][0].first =  dp[i-1][MAX-1].first + dp[i-1][MAX-1].second*MAX + (vec[i]^(MAX-1));
            dp[i][0].second = dp[i-1][MAX-1].second + 1;
        }

        forn(j,1,MAX){ 
            dp[i][j] = dp[i-1][j];
            if(dp[i][j].first < dp[i-1][j-1].first + dp[i-1][j-1].second*MAX + (vec[i]^(j-1))){
                dp[i][j].first =  dp[i-1][j-1].first + dp[i-1][j-1].second*MAX + (vec[i]^(j-1));
                dp[i][j].second = dp[i-1][j-1].second;
            }
        }
    }

 
    // trace(
    //     forn(i,0,n){
    //         forn(j,0,10){
    //             cout << setw(4) << (dp[i][j].first < -INF/2 ? -1 : dp[i][j].first) << " ";
    //         }
    //         cout << ln;
    //     }
    // );

    ll resp = 0;
    forn(j,0,MAX) resp = max(resp, dp[n-1][j].first);
    cout << resp << ln;
    return 0;
}
