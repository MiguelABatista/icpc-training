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

vector<pll> moves = {
    {-1, -1},
    {-1, 0},
    {-1, +1},
    {0, -1},
    {0, +1},
    {+1, -1},
    {+1, 0},
    {+1, +1},
};

bool next(char c, char d){
    return ((ll)(d)-(ll)(c)) == 1;
}

int main() {
    _; ll n, m; cin >> n >> m;
    vector<string> grid(n);
    forn(i, 0, n) cin >> grid[i];

    vector<vll> g(n*m);

    forn(i, 0, n)
    forn(j, 0, m){
        for(auto [t1, t2] : moves){
            ll x = i + t1, y = j+t2;
            if(x < 0 || x >= n || y < 0 || y >= m) continue;
            if(next(grid[i][j], grid[x][y])) g[m*i + j].push_back(m*x + y);
        }
    }

    vll dp(n*m, -1);

    function<ll (ll)> dfs = [&](ll curr){
        if(dp[curr] != -1) return dp[curr];

        ll b = 0;
        for (auto nxt : g[curr]) b = max(b, dfs(nxt));

        return dp[curr] = b+1;
    };


    ll best = 0;
    forn(i, 0, n*m) best = max(best,dfs(i));

    cout << best << ln;
    return 0;
}
