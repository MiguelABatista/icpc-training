#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

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
    ll n,m ; cin >> n >> m;
    vector<v64> g(n);
    forn(i,0,m){
        ll a, b; cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }

    v64 dp(n, -1);
    
    function<void (ll)> dfs = [&](ll u){
        ll resp = (u == n-1);
        for(ll v: g[u]){
            if(dp[v] == -1) dfs(v);
            resp = (resp + dp[v])%MOD;
        }
        dp[u] = resp;
    };

    dfs(0);
    cout << dp[0] << ln;
    return 0;
}
