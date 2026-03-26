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

int main() {
    _;
    ll n, m; cin >> n >> m;
    
    vector<v64> g(n);

    forn(i,0,m){
        ll a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
    }

    set<p64> invalid;
    v64 vis(n, -1);
    stack<ll> path;
    function<bool (ll)> dfs = [&](ll u){
        vis[u] = 0;
        if(u == n-1){
            vis[u] = 1;
            path.push(u);
            return true;
        }

        for(ll v: g[u]){
            if(vis[v] != -1) continue;
            if(dfs(v)){
                vis[u] = 1;
                path.push(u);
                invalid.insert({u,v});
                return true;
            }
        }

        return false; 
    };

    dfs(0);

    debugv(vis);
    forn(i,0,n) if(vis[i] == 0) vis[i] = -1;
    debugv(vis);
    queue<ll> q;

    v64 resp;

    while(!path.empty()){
        ll x = path.top();
        resp.push_back(x);
        path.pop();
        q.push(x);
        vis[x] = 0;
        debug(x);
        while(!q.empty()){
            ll u = q.front();
            
            if(vis[u] == -1) vis[u] = 0;
            debug(u);
            q.pop();
            for(ll v : g[u]){
                trace(
                    cout << u << " " << v << ln;
                );
 
                if(invalid.count({u,v})) continue;
                if(vis[v] == 0) continue;
                if(vis[v] == -1){
                    debug(1);
                    q.push(v);
                    continue;
                }
                debug(2);

                ll y = -1;                
                while(true){
                    y = path.top(); 
                    if(y == v) break;
                    vis[y] = 0;
                    path.pop();
                    q.push(y);
                }
            }
        } 
    }

    sort(resp.begin(), resp.end());
    cout << sz(resp) << ln; 
    forn(i,0, sz(resp)) cout << resp[i]+1 << " \n"[i == sz(resp)-1];
    return 0;
}
 