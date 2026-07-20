#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for(ll i = (s); i < (e); i++)
#define sz(u) ((ll)u.size())
#define ln "\n"

#define _ ios::sync_with_stdio(0); cin.tie(0)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
    
struct dinitz {
    const bool scaling;
    ll lim;
    struct edge {
        ll to, cap, rev, flow;
        bool res;
        edge(ll to_, ll cap_, ll rev_, bool res_)
            : to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
    };

    vector<vector<edge>> g;
    vll lev, beg;
    ll F;
    dinitz(ll n, bool scaling_) : scaling(scaling_), g(n), F(0) {}

    void add(ll a, ll b, ll c){
        g[a].emplace_back(b,c,sz(g[b]), false);
        g[b].emplace_back(a,0,sz(g[a])-1, true);
    }

    bool bfs(ll s, ll t){
        lev = vll(sz(g), -1); lev[s] = 0;
        beg = vll(sz(g), 0);
        queue<ll> q; q.push(s);
        while(sz(q)) {
            ll u = q.front(); q.pop();
            for (auto& i : g[u]) {
                if (lev[i.to] != -1 || (i.flow == i.cap)) continue;
                if (scaling && i.cap - i.flow < lim) continue;
                lev[i.to] = lev[u] + 1;
                q.push(i.to);
            }
        }
        return lev[t] != -1;
    }

    ll dfs(ll v, ll t, ll f = INF){
        if(!f || v==t) return f;
        for(ll& i = beg[v]; i < sz(g[v]); i++){
            auto& e = g[v][i];
            if(lev[e.to] != lev[v] + 1) continue;
            ll foi = dfs(e.to, t, min(f, e.cap - e.flow));
            if(!foi) continue;
            e.flow += foi, g[e.to][e.rev].flow -= foi;
            return foi;
        }
        return 0;
    }

    ll max_flow(ll s, ll t){
        for(lim = scaling ? (1ll<<30) : 1; lim; lim /=2)
            while (bfs(s,t)) while(ll ff = dfs(s,t)) F += ff;
        return F;
    }
    vector<pll> min_cut() {
        vector<pll> cut;
        forn(u,0,sz(g))
            if(lev[u] != -1)
                for(auto& e:g[u])
                    if (lev[e.to] == -1 && !e.res)
                        cut.push_back({u,e.to});
        return cut;
    }

    void reset() {
        F = 0;
        for(auto& edges : g) for(auto& e : edges) e.flow = 0;
    }
};

int main(){
    _;
    ll n, m; cin >> n >> m;
    dinitz fluxo(n, true);
    
    forn(i,0,m){
        ll a, b;
        cin >> a >> b;
        a--, b--;
        fluxo.add(a,b,1);
    }

    ll k = fluxo.max_flow(0,n-1);
    vector<vll> g(n);
    auto gf = fluxo.g;
    forn(i,0,n){
        for(auto [to, cap, rev, flow, res] : gf[i]){
            if(res) continue;
            if(flow == 0) continue;
            g[i].push_back(to);
        }
    }

    cout << k << ln;
    vll resp;
    for(ll v: g[0]){
        resp.push_back(0);
        resp.push_back(v);
        while (v != n-1){
            ll nv = g[v].back();
            g[v].pop_back();
            v = nv;
            resp.push_back(v);
        }
        cout << sz(resp) << ln;
        forn(i,0,sz(resp)) cout << resp[i] + 1 << " \n"[i==sz(resp) -1];
        resp.clear();
    }
    return 0;
}