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

struct dsu {
	vector<ll> id, sz;
	vector<ll> menor;

	dsu(ll n) : id(n), sz(n, 1), menor(n,INF) { iota(id.begin(), id.end(), 0);}

	ll find(ll a) { return a == id[a] ? a : id[a] = find(id[a]); }

	void uni(ll a, ll b, ll w) {
		a = find(a), b = find(b);
		if (a == b){
            menor[a] = min(menor[a], w);
            menor[a] = min(menor[a], menor[b]);
            return;
        }
		if (sz[a] < sz[b]) swap(a, b);
		sz[a] += sz[b], id[b] = a;
        menor[a] = min(menor[a], w);
        menor[a] = min(menor[a], menor[b]);
	}

    ll menor_um(){
        return menor[find(0)];
    }
};

void solve(){
    ll n, m; cin >> n >> m;
    vector<pair<ll, p64>> edges(m);

    dsu sdu(n);

    forn(i,0,m){
        ll a,b, w; cin >> a >> b >> w;
        a--;b--;
        edges[i] = {w,{a,b}};
    }

    sort(edges.begin(), edges.end());

    ll menor_aresta = INF;
    ll resp = INF;
    for(auto e: edges){
        sdu.uni(e.second.first, e.second.second, e.first);
        menor_aresta = sdu.menor_um();

        if(sdu.find(0) == sdu.find(n-1)){
            resp = min(resp, (menor_aresta + e.first));
        }
    }
    cout << resp << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve(); 

    return 0;
}