#include <bits/stdc++.h>
using namespace std;

typedef int ll;
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

const ll INF = 1'000'000'000;
const ll LIM = 70;
const ll MAX = 100'010;


ll n;
v64 cores;
vector<v64> g;
v64 cor_freq;
vector<v64> inv_cor;

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(){};
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (ll pw = 1, k = 1; (pw<<1) <= (ll)V.size(); pw <<= 1, ++k) {
            jmp.emplace_back((ll)V.size() - (pw<<1) + 1);
            for (ll i = 0; i < (ll)jmp[k].size(); ++i)
                jmp[k][i] = min(jmp[k-1][i], jmp[k-1][i + pw]);
        }
    }
    T query(ll l, ll r) const { // [l, r)
        ll len = r - l;
        ll dep = 63 - __builtin_clzll((unsigned long long)len);
        return min(jmp[dep][l], jmp[dep][r - (1LL<<dep)]);
    }
};

struct LCA {
    ll n;
    v64 first, depth, euler, euler_depth;
    RMQ<pair<ll,ll>> rmq; // (depth, idx_no_euler)

    LCA(vector<v64>& adj, ll root = 0)
        : n((ll)adj.size()), first(n, -1), depth(n, 0){
        euler.reserve(2*n-1);
        euler_depth.reserve(2*n-1);
        dfs(adj, root, -1, 0);
        vector<pair<ll,ll>> st; st.reserve(euler.size());
        for (ll i = 0; i < (ll)euler.size(); ++i)
            st.emplace_back(euler_depth[i], i);
        rmq = RMQ<pair<ll,ll>>(st);
    }

    void dfs(vector<v64>& adj, ll v, ll p, ll h) {
        depth[v] = h;
        if (first[v] == -1) first[v] = (ll)euler.size();
        euler.push_back(v);
        euler_depth.push_back(h);

        for (ll u : adj[v]) if (u != p) {
            dfs(adj, u, v, h+1);
            euler.push_back(v);
            euler_depth.push_back(h);
        }
    }

    ll lca(ll a, ll b) const {
        ll L = first[a], R = first[b];
        if (L > R) swap(L, R);
        auto ans = rmq.query(L, R+1);
        return euler[ans.second];
    }

    inline ll dist(ll a, ll b) const {
        ll c = lca(a, b);
        return depth[a] + depth[b] - 2*depth[c];
    }
};


void bfs(ll cor, v64& resp){
    v64 dist(n, -1);
    
    queue<p64> q;

    for(ll c : inv_cor[cor]) q.push({0,c});

    while (!q.empty()){
        auto [d, u] = q.front();
        q.pop();
        
        if(dist[u] != -1) continue;
        
        dist[u] = d;
        resp[cores[u]] = min(resp[cores[u]], d);

        for(ll v: g[u]){
            if(dist[v] != -1) continue;
            q.push({d+1, v});
        }
    }
}

int main(){
    _;
    cin >> n;
    cores.resize(n);
    g.resize(n);
    cor_freq.resize(n,0);
    inv_cor.resize(n);

    forn(i,0,n){
        cin >> cores[i];
        cores[i]--;
        cor_freq[cores[i]]++;
        inv_cor[cores[i]].push_back(i);
    }
    
    forn(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    ll q; cin >> q;
    vector<p64> queries(q);
    v64 cor_freq2(n,0);
    
    forn(i,0,q){
        cin >> queries[i].first >> queries[i].second;
        queries[i].first--; queries[i].second--;
        cor_freq2[queries[i].first]++;
        cor_freq2[queries[i].second]++;
    }

    ll gordo_count = 0;
    v64 gordo(n, -1);

    forn(i,0,n){
        if(cor_freq[i] > LIM ){
            gordo[i] = gordo_count++; 
        }
    }

    vector<v64> resp_gordo(gordo_count, v64(n, INF));

    forn(i,0,n){
        if(gordo[i] == -1) continue;
            v64 dist(n, -1);
    
        queue<p64> que;

        for(ll c : inv_cor[i]) que.push({0,c});

        while (!que.empty()){
            auto [d, u] = que.front();
            que.pop();
            
            if(dist[u] != -1) continue;
            
            dist[u] = d;
            
            resp_gordo[gordo[i]][cores[u]] = min(resp_gordo[gordo[i]][cores[u]], d);

            for(ll v: g[u]){
                if(dist[v] != -1) continue;
                que.push({d+1, v});
            }
        }

        
    }

    LCA lca(g);

    forn(i,0,q){
        auto [a,b] = queries[i];

        if(gordo[cores[b]] != -1) swap(a,b);
        
        if(gordo[cores[a]] != -1) {
            cout << resp_gordo[gordo[cores[a]]][cores[b]] << ln;
            continue;
        }
        
        ll resp = INF;
        for(ll u : inv_cor[cores[a]]){
            for(ll v: inv_cor[cores[b]]){
                resp = min(resp, lca.dist(u,v));
            }
        }
        cout << resp << ln;
    }
    return 0;
}
