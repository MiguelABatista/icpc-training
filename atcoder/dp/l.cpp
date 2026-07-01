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


int main() {
    _;
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    vector<vll> dp(n, vll(n));
    ll paridade = n%2;

    // t == 0
    forn(l,0,n){
        dp[l][l] = (paridade == 0 ? 1 : -1) * vec[l];
    }

    forn(t,1,n){
        forn(l,0,n-t){
            ll r = l + t;
            if(t%2 == paridade){ // Taro
                dp[l][r] = max(dp[l+1][r] + vec[l], dp[l][r-1] + vec[r]);
            }else{ // Jiro
                dp[l][r] = min(dp[l+1][r] - vec[l], dp[l][r-1] - vec[r]);
            }
        }
    }
    
    cout << -dp[0][n-1] << ln;
    return 0;
}
