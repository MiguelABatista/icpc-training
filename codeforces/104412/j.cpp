#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> v64;
typedef pair<ll,ll> p64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) (x).size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll LOG = 20;

ll n;
vector<v64> g;
vector<bool> visited;
vector<ll> tin, low;
ll timer = 0;


// Disjoint Set Union (Union-Find)
//
// Supports find with path compression and union by size to maintain dynamic connectivity of disjoint sets.
//
// complexity: O(alpha(N)) amortized per op, O(N)

struct dsu {
	v64 id, len;

	dsu(ll n_) : id(n_), len(n_, 1) { iota(id.begin(), id.end(), 0); }

	ll find(ll a) { return a == id[a] ? a : id[a] = find(id[a]); }

	void uni(ll a, ll b) {
		a = find(a), b = find(b);
		if (a == b) return;
		if (len[a] < len[b]) swap(a, b);
		len[a] += len[b], id[b] = a;
	}
};


void dfs(ll u, ll p, dsu& sdu) {
    visited[u] = true;
    tin[u] = low[u] = timer++;
    for(ll v : g[u]) {
        if (v==p) continue;

        if (visited[v]) {
            low[u] = min(low[u], tin[v]);
        } else {
            dfs(v, u, sdu);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                sdu.uni(v,u);
            }
        }
    }
}

void find_bridges(dsu& sdu) {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    forn(i, 0, n) {
        if (!visited[i]) dfs(i, -1, sdu);
    }
}

struct buceta {
    ll v = -1, esp_meu = -1, esp_dele = -1;
    ll tam_max = 0;
};

int main() {
    _;
    ll m, q; cin >> n >> m >> q;
    g.resize(n);

    vector<p64> edg; edg.reserve(m);
    forn(i, 0, m) {
        ll a, b; cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
        edg.emplace_back(a, b);
    }

    dsu sdu(n);

    find_bridges(sdu);

    forn(i, 0, q) {
        ll a, b; cin >> a >> b;
        a--; b--;
        
        if(sdu.find(a) == sdu.find(b)){
            cout << "YES" << ln;
        }else{
            cout << "NO" << ln;
        }
    }

    return 0;
}