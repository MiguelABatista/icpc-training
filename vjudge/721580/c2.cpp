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
v64 subsize;
v64 treesum;

p64 dfs1(ll u, ll p){
    p64 resp = {1,0}; // quantidade, soma

    for(ll v : g[u]){
        if(v == p) continue;
        p64 aux = dfs1(v,u);
        resp.first += aux.first;
        resp.second += aux.first + aux.second;
    }
    subsize[u] = resp.first;
    return resp;
}

void dfs2(ll u, ll p){
    if(p != -1){
        ll curr_resp = treesum[p];
        
        curr_resp += n - 2*subsize[u];
        
        treesum[u] = curr_resp;
    }

    for(ll v: g[u]){
        if(v == p) continue;
        dfs2(v,u);
    }
}

int main(){
    cin >> n;
    g.resize(n);
    treesum.resize(n,-1);
    subsize.resize(n, 0);

    forn(i,1,n){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    treesum[0] = dfs1(0,-1).second;

    dfs2(0,-1);
    // forn(i,0,n) cout << dfs1(i,-1).second << " \n"[i==n-1];
    forn(i,0,n) cout << treesum[i] << " \n"[i==n-1];

    return 0;

}