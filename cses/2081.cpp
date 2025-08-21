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

struct Bit {
	ll n;
	v64 bit;
	Bit(ll _n=0) : n(_n), bit(n + 1) {}
	Bit(v64& v) : n(v.size()), bit(n + 1) {
		for (ll i = 1; i <= n; i++) {
			bit[i] += v[i - 1];
			ll j = i + (i & -i);
			if (j <= n) bit[j] += bit[i];
		}
	}
	void update(ll i, ll x) { // soma x na posicao i
		for (i++; i <= n; i += i & -i) bit[i] += x;
	}
	ll pref(ll i) { // soma [0, i]
		ll ret = 0;
		for (i++; i; i -= i & -i) ret += bit[i];
		return ret;
	}
	ll query(ll l, ll r) {  // soma [l, r]
		return pref(r) - pref(l - 1); 
	}
	ll upper_bound(ll x) {
		ll p = 0;
		for (ll i = __lg(n); i+1; i--) 
			if (p + (1<<i) <= n and bit[p + (1<<i)] <= x)
				x -= bit[p += (1 << i)];
		return p;
	}
};

// Centroid decomposition
//
// decomp(0, k) computa numero de caminhos com 'k' arestas
// Mudar depois do comentario
//
// O(n log(n))
const ll MAX = 200'010;

vector<ll> g[MAX];
ll sz[MAX], rem[MAX];

void dfs(v64& path, ll i, ll l=-1, ll d=0) {
	path.push_back(d);
	for (ll j : g[i]) if (j != l and !rem[j]) dfs(path, j, i, d+1);
}

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

ll decomp(ll i, ll k1, ll k2) {
	ll c = centroid(i, i, dfs_sz(i));
	rem[c] = 1;
    debug(c);
    // gasta O(n) aqui - dfs sem ir pros caras removidos
	ll ans = 0;
	Bit cnt(sz[i]+1);
	cnt.update(0+1,1);
	for (ll j : g[c]) if (!rem[j]) {
		vector<ll> path;
		dfs(path, j);
        debug(j);
		for (ll d : path) if (k2 - (d+1) >= 0 && k1 - (d+1) <= sz[i]){            
            ll temp = cnt.query(max(k1-(d+1) + 1,0ll), min(k2-(d+1) + 1, sz[i]));
            debug(temp);
            ans += temp; 
        }
		for (ll d : path) cnt.update(d+1+1,1);
	}
	for (ll j : g[c]) if (!rem[j]) {
        ll temp = decomp(j,k1, k2);
        ans += temp; 
    }
	rem[c] = 0;
	return ans;
}

int main(){
    _;
    ll n; cin >> n;
    ll k1, k2; cin >> k1 >> k2;
    debug(k1);
    debug(k2);
    forn(i,0,n-1){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    cout <<  decomp(0,k1, k2) << ln;
    
    return 0;   
}