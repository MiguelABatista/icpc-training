#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

v64 sz;
vector<v64> g;

ll dfs(ll u){
    ll size_u = 1;

    for(auto v: g[u]){
        size_u += dfs(v);
    }

    sz[u] = size_u;
    // cout << u << ' ' << size_u << ln;
    return size_u;
}

int main(){
    _;
    ll n; cin >> n;
    g.resize(n);
    sz.resize(n,0);

    forn(i,1,n){
        ll x;
        cin >> x;
        x--;
        g[x].push_back(i);
    }

    dfs(0);
    for(auto x: sz) cout << x-1 << " ";
    cout << ln;

    return 0;
}