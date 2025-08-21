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

// Centroid Tree
//
// Constroi a centroid tree
// p[i] eh o pai de i na centroid-tree
// dist[i][k] = distancia na arvore original entre i
// e o k-esimo ancestral na arvore da centroid
//
// O(n log(n)) de tempo e memoria

const ll MAX = 100'010;
vector<v64> g(MAX), dist(MAX);
vector<ll> sz(MAX), rem(MAX), p(MAX);

ll dfs_sz(ll i, ll l=-1) {
	sz[i] = 1;
	for (ll j : g[i]) if (j != l and !rem[j]) sz[i] += dfs_sz(j, i);
	return sz[i];
}

ll centroid(ll i, ll l, ll size) {
	for (ll j : g[i]) if (j != l and !rem[j] and sz[j] > size / 2)
		return centroid(j, i, size);
	return i;
}

void dfs_dist(ll i, ll l, ll d=0) {
	dist[i].push_back(d);
	for (ll j : g[i]) if (j != l and !rem[j])
		dfs_dist(j, i, d+1);
}

void decomp(ll i, ll l = -1) {
	ll c = centroid(i, i, dfs_sz(i));
	rem[c] = 1, p[c] = l;
	dfs_dist(c, c);
	for (ll j : g[c]) if (!rem[j]) decomp(j, c);
}

void build(ll n) {
	forn(i,0,n) rem[i] = 0, dist[i].clear();
	decomp(0);
	forn(i,0,n) reverse(dist[i].begin(), dist[i].end());
}

int main(){
    _;
    ll n, q; cin >> n >> q;
    forn(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    v64 answer(n, INF);

    
    build(n);
    answer[0] = 0;
    ll anc = 0;
    ll cnt = 0;
    while(anc != -1){
        answer[anc] = min(answer[anc], dist[0][cnt]);
        anc = p[anc];
        cnt++;
    }

    while(q--){
        ll t, v; cin >> t >> v;
        v--;
        if(t == 1){ // pinta v de azul
            anc = v;
            cnt = 0;
            while(anc != -1){
                answer[anc] = min(answer[anc], dist[v][cnt]);
                anc = p[anc];
                cnt++;
            }
        }else{ // responde a dist pro vermelho mais próximo de v 
            ll resp = INF;
            anc = v;
            cnt = 0;
            while(anc != -1){
                debug(anc);
                debug(answer[anc]); 
                resp = min(resp, answer[anc]+dist[v][cnt]);
                anc = p[anc];
                cnt++;
            }   
            cout << resp << ln;
        }
    }
    return 0;
}