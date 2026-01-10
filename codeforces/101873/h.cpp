#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _;
    ll n, r, h, m; cin >> n >> r >> h >> m;
    r--; h--; m--;

    vector<v64> g(n);
    forn(i, 0 ,n-1) {
        ll a, b; cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // opt 2
    function<p64 (ll,ll,ll)> dfs = [&](ll u, ll p, ll height) {
        p64 res = {height, 0};
        if (u == r) res.second = 1;
        for (auto v : g[u]) {
            if (v == p) continue;
            auto tmp = dfs(v, u, height+1);
            if (tmp.second) res.second = 1;
            res.first = max(res.first, tmp.first);
        }
        return res;
    };


    // opt 1
    ll mx = INF;
    forn(i, 0, n) {
        if (i == h || i == m) continue;
        mx = min(mx, 1 + dfs(i, -1, 0).first);
        
    }

    ll mx2 = 0;
    for(auto v : g[h]) {
        auto tmp = dfs(v, h, 1);
        if (tmp.second) mx2 = tmp.first;
    }

    ll mx3 = 0;
    for (auto v : g[m]) {
        auto tmp = dfs(v, m, 1);
        if (tmp.second) mx3 = tmp.first;
    }

    cout << min({mx, mx2, mx3}) << ln;
    return 0;
}