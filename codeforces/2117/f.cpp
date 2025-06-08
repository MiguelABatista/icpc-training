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

const ll MOD = 1'000'000'007;

inline ll sum(ll a, ll b) { a += b; if (a >= MOD) a -= MOD; return a; }
inline ll sub(ll a, ll b) { a -= b; if (a < 0)  a += MOD; return a; }
inline ll mult(ll a, ll b) { return (a * b) % MOD; }

inline ll pot(ll base, ll exp) {
    if(exp == 0) return 1;
    if(exp == 1) return base;

    ll aux = pot(base, exp/2);
    ll res = mult(aux, aux);
    if(exp % 2 == 1) res = mult(res, base);

    return res;
}

inline ll inv_mod(ll a) {return pot(a, MOD-2);}

void dfs(ll u, ll p, v64& subsize, vector<v64>& g){
    ll curr_size = 0;
    for(ll v: g[u]){
        if(v == p) continue; 

        dfs(v,u, subsize, g);

        curr_size += subsize[v];
    }

    subsize[u] = curr_size + 1;
}


void solve(){
    ll n; cin >> n;
    vector<v64> g(n);
    v64 subsize(n, 0);

    forn(i,0,n-1){
        ll a,b; cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    ll leafs = 0;
    ll deg3 = 0;

    forn(i,1,n){
        if(g[i].size() == 1){
            leafs++;
        }
        if(g[i].size() == 3){
            deg3 = i;
        }
    }
    
    if(leafs > 2){
        cout << 0 << ln;
        return;
    }

    if(leafs == 1){
        cout << pot(2,n) << ln;
        return;
    }

    dfs(0,-1, subsize, g);

    v64 vaux = {};

    debug(deg3);
    for(ll v: g[deg3]) vaux.push_back(subsize[v]);
    
    sort(vaux.begin(), vaux.end());

    ll val1 = vaux[0];
    ll val2 = vaux[1];

    debug(val1);
    debug(val2);

    ll trava1;
    ll trava2;

    if(val1 < val2){
        trava1 = 2*val1;
        trava2 = 2*val1+1;
    }else{
        trava1 = 2*val1;
        trava2 = 2*val1;
    }
    
    debug(trava1);
    debug(trava2);

    ll resto1 = n - trava1;
    ll resto2 = n - trava2;
    cout << sum(pot(2,resto1), pot(2,resto2)) << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve(); 

    return 0;
}