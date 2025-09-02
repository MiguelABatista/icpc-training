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
const ll MAX = 200'010;
const ll MAXLOG = 20;


// LCA com binary lifting
//
// Assume que um vertice eh ancestral dele mesmo, ou seja,
// se a eh ancestral de b, lca(a, b) = a
// MAXLOG = ceil(log(MAX))
//
// Complexidades:
// build - O(n log(n))
// lca - O(log(n))

vector<v64> g(MAX);
ll n, m, p;
ll parent[MAXLOG][MAX];
ll in[MAX], out[MAX];
v64 acc, resp;

void dfs(ll k) {
	in[k] = p++;
    for(ll v: g[k]){
        if(in[v] == -1){
            parent[0][v] = k;
            dfs(v);
        }
    }
	out[k] = p++;
}

void build(ll raiz) {
	forn(i,0,n) parent[0][i] = i;
	p = 0, memset(in, -1, sizeof in);
	dfs(raiz);
	forn(k,1,MAXLOG) forn(i,0,n)
		parent[k][i] = parent[k - 1][parent[k - 1][i]];
}

bool anc(ll a, ll b) { // se a eh ancestral de b
	return in[a] <= in[b] and out[a] >= out[b];
}

ll lca(ll a, ll b) {
	if (anc(a, b)) return a;
	if (anc(b, a)) return b;
	for (ll k = MAXLOG - 1; k >= 0; k--)
		if (!anc(parent[k][a], b)) a = parent[k][a];
	return parent[0][a];
}

void dfs2(ll u, ll pa){
    ll ans = acc[u];
    
    for(ll v : g[u]){
        if(v == pa) continue;
        dfs2(v,u);
        ans += resp[v];
    }
    resp[u] = ans;
}

int main(){
    _;
    cin >> n >> m;

    g.resize(n);
    acc.resize(n);
    resp.resize(n);

    forn(i,1,n){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }  

    build(0);

    forn(i,0,m){
        ll a, b; cin >> a >> b;
        a--, b--;
        ll lac = lca(a,b);
        acc[a]++;
        acc[b]++;
        acc[lac]--;
        if(parent[0][lac] != lac) acc[parent[0][lac]]--;
    }

    dfs2(0,-1);
    forn(i,0,n) cout << resp[i] << " ";; cout << ln;
    // forn(i,0,n) cout << acc[i] << " ";; cout << ln;
    return 0;
}
