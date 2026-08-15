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
    vector<vll> g(n);
    forn(i,1,n){
        ll a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vll sub(n);
    vll pai(n);

    function<void (ll, ll)> dfs2 = [&](ll u, ll p){
        pai[u] = p;
        ll resp = 1;
        for(ll v : g[u]){
            if(v == p) continue;
            dfs2(v,u);
            resp += sub[v];
        }
        sub[u] = resp;
    };

    dfs2(0,-1);

    function<void (ll, ll, vll&, ll)> dfs = [&](ll u, ll p, vll& d, ll h){
        
    };

    forn(i,0,n){
        vector<pll> filhos;
        for(ll j: g[i]){
            if(j == pai[i]) filhos.push_back({n-sub[i], j});
            else filhos.push_back({sub[j], j});
        }

        sort(filhos.begin(), filhos.end());

    }
    return 0;
}
