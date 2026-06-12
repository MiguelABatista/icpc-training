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

int main() {
    _;
    ll n, w; cin >> n >> w;
    vector<pll> vec(n);
    forn(i,0,n) cin >> vec[i].first >> vec[i].second;

    vll dp(w+1);

    forn(i,0,n){
        for(ll p = w; p >= 0; p--){
            if(p < vec[i].first) continue;
            dp[p] = max(dp[p], dp[p-vec[i].first] + vec[i].second);
        }
    }
    ll resp = 0;
    forn(i,0,w+1) resp = max(resp, dp[i]);
    cout << resp << ln;
    return 0;
}
