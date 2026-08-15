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

tuple<ll,ll,ll> find_middle(vector<vll>& g){
    ll n = sz(g);

    vll d(n,INF);
    queue<ll> q;
    q.push(0);
    d[0] = 0;
    
    while (!q.empty()){
        ll u = q.front();
        q.pop();
        for(ll v : g[u]) if(d[v] == INF){
            d[v] = d[u] + 1;
            q.push(v);
        }
    }
    
    ll best = 0;
    forn(i,0,n) if(d[best] < d[i]) best = i;
    

    ll root = best;
    vll dep(n);
    vll pai(n);
    
    function<void (ll, ll)> dfs = [&](ll u, ll p){
        if(p != -1) dep[u] = dep[p] + 1;
        pai[u] = p;
        for(ll v: g[u]) if(v != p) dfs(v,u);
    };

    dfs(root, -1);

    ll ext = 0;
    forn(i,0,n) if(dep[i] > dep[ext]) ext = i;
    ll diam = dep[ext];
    forn(i,0,diam/2) ext = pai[ext];
    return {ext, pai[ext], diam};
};

void solve() {
    _;
    ll n; cin >> n;
    vector<vll> g(n);
    forn(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    if(n == 2){
        cout << "1 1\n";
        return; 
    }
    auto [a,b, diam]= find_middle(g);
    ll m = diam/2;

    vll depa(n);
    vll depb(n);
    vll hasa(n);
    vll hasb(n);
    depa[b] = -1;
    depb[a] = -1;
    vll as;
    vll bs;


    function<void (ll ,ll)> dfsa = [&](ll u, ll p){
        depa[u] = depa[p] + 1;

        ll cnt = 0;
        for(ll v : g[u]) if(v != p){
            dfsa(v,u);
            if(hasa[v]) cnt++;
        }
        if(depa[u] == m) hasa[u] = 1;
        if(cnt > 0) hasa[u] = cnt;
        if(cnt > 1) as.push_back(depa[u]);
    };

    function<void (ll ,ll)> dfsb = [&](ll u, ll p){
        depb[u] = depb[p] + 1;

        ll cnt = 0;
        for(ll v : g[u]) if(v != p){
            dfsb(v,u);
            if(hasb[v]) cnt++;
        }
        if(depb[u] == m) hasb[u] = 1;
        if(cnt > 0) hasb[u] = cnt;
        if(cnt > 1) bs.push_back(depb[u]);
    };

    dfsa(a,b);
    dfsb(b,a);
    sort(as.begin(), as.end());
    sort(bs.begin(), bs.end());
    as.push_back(m);
    bs.push_back(m);
    as.erase(unique(as.begin(), as.end()), as.end());
    bs.erase(unique(bs.begin(), bs.end()), bs.end());

    vll resp;
    forn(i,0,sz(as)) forn(j,0,sz(bs)) resp.push_back(as[i] + bs[j]+1);
    sort(resp.begin(), resp.end());
    resp.erase(unique(resp.begin(), resp.end()), resp.end());

    cout << sz(resp) << " ";
    forn(i,0,sz(resp)) cout << resp[i] << " \n"[i == sz(resp)-1];    
    
    trace(cout << "---------------\n\n";)
    return;   
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
