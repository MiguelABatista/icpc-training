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
const ll MAX = 100'005;
// const ll MAX = 101;

int main() {
    _;
    ll n, w; cin >> n >> w;
    vector<pll> vec(n);
    forn(i,0,n) cin >> vec[i].first >> vec[i].second;

    vll dp(MAX, INF);
    dp[0] = 0;
    forn(j,0,n){
        for(ll i = MAX-1; i >= 0; i--){
            if(i-vec[j].second < 0) continue;
            dp[i] = min(dp[i], dp[i-vec[j].second] + vec[j].first); 
        }
    }

    ll resp = 0; 
    forn(i,0,MAX) if(dp[i] <= w) resp = max(resp, i);
    cout << resp << ln;
    return 0;
}
