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
    ll n, m; cin >> n >> m;
    vector<vll> g(n);
    forn(i,0,m){
        ll a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vll vis(n);
    vll resp;
    ll fim = -1;
    function<bool (ll, ll)> dfs = [&](ll u, ll p){
        vis[u] = 1;
        for(ll v: g[u]){
            if(v == p) continue;
            if(vis[v]){
                trace( cout << "1: " << u << " " << p << " " << v << ln;)
                fim = v;
                resp.push_back(v);
                resp.push_back(u);
                return true;
            }
            if(dfs(v, u)){
                trace( cout << "2: " << u << " " << p << " " << v << ln;)
                resp.push_back(u);
                return !(u == fim);
            }
            if(fim != -1) return false;
        }
        return false;
    };

    forn(i,0,n){
        if(vis[i]) continue;
        dfs(i, -1);
        if(fim != -1) break;
    }
    
    if(fim != -1){
        cout << sz(resp) << ln;
        forn(i,0,sz(resp)) cout << resp[i] + 1<< " \n"[i==sz(resp)-1];
    }else{
        cout << "IMPOSSIBLE" << ln;
    }
    return 0;
}
