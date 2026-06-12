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
const ll MAX = 16;

int main() {
    _;
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n){ 
        string s; cin >> s;
        vec[i] = stoi(s, 0, 16);
    }

    vector<vector<ll>> dp(n, vector<ll>(n+1, -INF));

    forn(i,0,n) dp[i][0] = 0;

    dp[0][1] = vec[0]^0;

    forn(i,1,n){
        forn(j,1,n+1){
            dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] + (vec[i]^(j-1)));
        }
    }

    ll resp = 0;

    trace(
        forn(i,0,n){
            forn(j,0,n){
                cout << setw(4) << (dp[i][j] < -INF/2 ? -1 : dp[i][j]) << " ";
            } 
            cout << ln;
        }
    );

    forn(j,0,n+1) resp = max(resp, dp[n-1][j]);
    cout << resp << ln;
    return 0;
}
