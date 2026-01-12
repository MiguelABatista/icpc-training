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


struct dinitz{
    const bool scaling = true;
    ll lim;
    struct edge {
        ll to, cap, rev, flow;
        bool res;
        edge(ll to_, ll cap_, ll rev_, bool res_) 
            : to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
        
    };
    
    vector<vector<edge>> g;
    vector<ll> lev, beg;
    ll F;

    dinitz(ll n) : g(n), F(0) {}

    void add(ll a, ll b, ll c){
        g[a].emplace_back(b, c, g[b].size(), false);
        g[b].emplace_back(a, 0, g[a].size()-1, true);
    }

    bool bfs(ll s, ll t){
        lev = vector<ll>(g.size(), -1); lev[s] = 0;
        beg = vector<ll>(g.size(), 0);
        queue<ll> q; q.push(s);

        while(q.size()){
            ll u = q.front(); q.pop();
            for(auto& i: g[u]){
                if(lev[i.to] != -1 or (i.flow == i.cap)) continue;
                if(scaling and i.cap - i.flow < lim) continue;
                lev[i.to] = lev[u] + 1;
                q.push(i.to);
            }
        }
        return lev[t] != -1;
    }

    ll dfs(ll v, ll s, ll f = INF){
        if(!f or v == s) return f;
        for(ll& i = beg[v]; i < g[v].size(); i++){
            auto& e = g[v][i];
            if(lev[e.to] != lev[v] + 1) continue;
            ll foi = dfs(e.to, s, min(f, e.cap - e.flow));
            if(!foi) continue;
            e.flow += foi, g[e.to][e.rev].flow -= foi;
            return foi;
        }
        return 0;
    }

    ll max_flow(ll s, ll t){
        for(lim = scaling ? (1<<30) : 1 ; lim; lim /= 2)
            while(bfs(s,t)) while(ll ff = dfs(s,t)) F += ff;
        return F;
    }

    void reset(){
        F = 0;
        for(auto& edges : g) for (auto& e: edges) e.flow = 0; 
    }
};

int main() {
    _;
    ll m, n, k; cin >> m >> n >> k;
    // sockets 0 - m-1
    // devices m - m+n-1
    // source m+n
    // tink m+n+1
    ll S = m + n;
    ll T = m + n + 1;
    dinitz d(m+n+2);

    forn(i, 0, k) {
        ll a, b; cin >> a >> b;
        b += m;
        a--; b--;
        d.add(a, b, 1);
    }
    forn(i, 0, m) {
        d.add(S, i, 1);
    }
    forn(i, m, m+n) {
        d.add(i, T, 1);
    }

    ll ans = d.max_flow(S, T);

    vector<set<ll>> g(n+m);

    vector<bool> isp(n+m);

    forn(i, 0, m+n) {
        for (auto edg : d.g[i]) {
            if (edg.flow == edg.cap) {
                if(edg.to == T) {
                    isp[i] = true;
                }
                continue;
            }
            if (edg.to == S || edg.to == T) continue;
            g[i].insert(edg.to);
        }
    }

    
    vector<ll> visited(m+n);
    vector<p64> mud_g;
    vector<ll> mud_isp;
    
    function<bool (ll u)> dfs = [&](ll u) {
        visited[u] = true;
        if (!isp[u] && u >= m) {
            isp[u] = true;
            mud_isp.push_back(u);
            return true;
        }

        for(ll v: g[u]){
            if (visited[v]) continue;

            if (dfs(v)) {
                mud_g.push_back({u,v});
                g[v].insert(u);
                g[u].erase(v);
                return true;
            }
        }
        return false;        
    };
    
    ll base = ans;
    forn(i, 0, m) {
        visited.assign(n+m, false);
        ll resp = base;

        if (dfs(i)) {
            resp++;
            if (dfs(i)) resp++;
        }

        ans = max(ans, resp);
        for(ll x: mud_isp) isp[x] = false;
        for(auto p: mud_g){
            auto [u,v] = p;
            g[v].erase(u);
            g[u].insert(v);
        }

        mud_isp.clear();
        mud_g.clear();
    }

    cout << ans << ln;
    
    return 0;
}