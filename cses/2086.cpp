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

v64 prefsum;
v64 vec;
vector<ll> dp_before, dp_cur;

inline ll sq(ll a){ return a*a;}
inline ll cost(ll l, ll r){ return sq(prefsum[r] - (l == 0 ? 0 : prefsum[l-1]));}



// Divide and Conquer DP
//
// Particiona o array em k subarrays
// minimizando o somatorio das queries
//
// O(k n log n), assumindo quer cost(l, r) eh O(1)

vector<v64> dp; // dp[n+1][2]

void solve(ll k, ll l, ll r, ll lk, ll rk) {
	if (l > r) return;
	ll m = (l+r)/2, p = -1;
	auto& ans = dp[m][k&1] = INF;
	for (ll i = max(m, lk); i <= rk; i++) {
		ll at = dp[i+1][~k&1] + cost(m, i);
		if (at < ans) ans = at, p = i;
	}
	solve(k, l, m-1, lk, p), solve(k, m+1, r, p, rk);
}

ll dnc(ll n, ll k) {
	dp[n][0] = dp[n][1] = 0;
	forn(i,0,n) dp[i][0] = INF;
	forn(i,1,k+1) solve(i, 0, n-i, 0, n-i);
	return dp[0][k&1];
}

int main(){
    _;
    ll n, k;
    cin >> n >> k;
    vec.resize(n);
    prefsum.resize(n);
    dp.resize(n+1 ,v64(2,0));

    for(auto& v:vec) cin >> v;
    
    prefsum[0] = vec[0];
    forn(i,1,n) prefsum[i] = prefsum[i-1] + vec[i];

    cout << dnc(n, k) << ln;
    return 0;
}