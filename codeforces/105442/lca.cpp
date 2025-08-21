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
const ll MAX = 100'010;
const ll MAXLOG = 20;

vector<v64> g(MAX);
ll n, p;
ll pai[MAXLOG][MAX];
ll in[MAX], out[MAX];

void dfs(ll k){
    in[k] = p++;
    forn(i,0,g[k].size())
        if(in[g[k][i]] == -1){
            pai[0][g[k][i]] = k;
            dfs(g[k][i]);
        }
    out[k] = p++;
}

void build(ll raiz){
    for(ll i = 0; i < n; i++) pai[0][i] = 1;
    p = 0, memset(in, -1, sizeof in);
    forn(k,1,MAXLOG) forn(i,0,n)
        pai[k][i] = pai[k-1][pai[k-1][i]];
}

bool anc(ll a, ll b){
    return in[a] <= in[b] and out[a] >= out[b];
}

ll lca(ll a, ll b){
    if(anc(a,b)) return a;
    if(anc(b,a)) return b;

    for(ll k = MAXLOG-1; k >= 0; k--)
        if(!anc(pai[k][a], b)) a = pai[k][a];

    return pai[0][a];
}

