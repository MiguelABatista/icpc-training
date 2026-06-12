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

void solve(){
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    vll dp(n);
    dp[n-1] = vec[n-1];
    for(ll i = n-2; i>= 0; i--){
        if(vec[i]-vec[i+1] > dp[i+1]){
            dp[i] = vec[i];
        }else{
            dp[i] = max(dp[i+1]+1, vec[i]);
        }
    }
    ll resp = 0;
    debugv(dp);
    forn(i,0,n) resp = max(resp, dp[i]);
    cout << resp << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
