#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
const ll MAX = 10;
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
const ll MAX = 50'005;
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    _;
    ll n, m; cin >> n >> m;
    vector<vll> g(n);
    forn(i,0,m){
        ll a, b; 
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
    }

    vector<bitset<MAX>> mem(n);
    vll vis(n);
    vll resp(n);

    function<void (ll)> dfs = [&](ll u){
        vis[u] = 1;
        mem[u][u] = 1;
        for(ll v: g[u]){
            if(!vis[v]) dfs(v);
            mem[u] |= mem[v];
        }
        resp[u] = mem[u].count();
    };

    forn(i,0,n) if(!vis[i]) dfs(i);

    forn(i,0,n) cout << resp[i] << " \n"[i==n-1];
    return 0;
}
