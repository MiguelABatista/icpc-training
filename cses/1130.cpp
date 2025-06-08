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

vector<v64> g;
v64 dp;

void dfs(ll u, ll p){
    ll resp = 0;

    for(ll v : g[u]){
        if(v == p) continue;
        
    }
}

int main(){
    ll n; cin >> n;
    g.resize(n);
    dp.resize(n,-1);

    forn(i,1,n){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0, -1);

    forn(i,0,n) cout << sub[i] << " \n"[i==n-1];
    return 0;

}