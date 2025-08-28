#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll n;
vector<v64> g;
v64 colors, resp;
vector<set<ll>> cores;
v64 dono;


void dfs(ll u, ll p) {
    ll big = -1;
    ll sz = 0;
    for(ll v: g[u]){
        if(v == p) continue;
        dfs(v,u);
        if(cores[dono[v]].size() > sz){
            big = v;
            sz = cores[dono[v]].size();
        }
    }

    // debug(u);
    // debug(big);
    if(big == -1){
        cores[u].insert(colors[u]);
        dono[u] = u;
        resp[u] = 1;
        return;
    }

    dono[u] = dono[big];
    cores[dono[u]].insert(colors[u]);
    for(ll v: g[u]){
        if(v == p) continue;
        if(v == big) continue;
        for(ll c: cores[dono[v]]){
            cores[dono[u]].insert(c);
        }
    }
    resp[u] = cores[dono[u]].size();
}


int main(){
    _;
    cin >> n;

    g.resize(n);
    colors.resize(n);
    resp.resize(n);
    dono.resize(n);
    cores.resize(n);

    forn(i,0,n) cin >> colors[i];

    forn(i,1,n){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }  

    dfs(0,-1);

    forn(i,0,n) cout << resp[i] << " ";; cout << ln;

    return 0;
}
