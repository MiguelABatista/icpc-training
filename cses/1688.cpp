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
ll n, p;
ll pai[MAXLOG][MAX];
ll in[MAX], out[MAX];

void dfs(ll k) {
	in[k] = p++;
    for(ll v: g[k]){
        if(in[v] == -1){
            pai[0][v] = k;
            dfs(v);
        }
    }
	out[k] = p++;
}

void build(ll raiz) {
	forn(i,0,n) pai[0][i] = i;
	p = 0, memset(in, -1, sizeof in);
	dfs(raiz);

	// pd dos pais
	forn(k,1,MAXLOG) forn(i,0,n)
		pai[k][i] = pai[k - 1][pai[k - 1][i]];
}

bool anc(ll a, ll b) { // se a eh ancestral de b
	return in[a] <= in[b] and out[a] >= out[b];
}

ll lca(ll a, ll b) {
	if (anc(a, b)) return a;
	if (anc(b, a)) return b;

	// sobe a
	for (ll k = MAXLOG - 1; k >= 0; k--)
		if (!anc(pai[k][a], b)) a = pai[k][a];

	return pai[0][a];
}


int main(){
    _;
    ll q; cin >> n >> q;
    g.resize(n);

    forn(i,1,n){
        ll aux;
        cin >> aux;
        aux--;
        g[aux].push_back(i);
        g[i].push_back(aux);
    }  

    build(0);

    while(q--){
        ll a, b; cin >> a >> b;
        a--; b--;
        cout << lca(a,b)+1 << ln;
    }

    return 0;
}
