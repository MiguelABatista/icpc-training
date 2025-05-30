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

struct dsu {
	vector<ll> id, sz;

	dsu(ll n) : id(n), sz(n, 1) { iota(id.begin(), id.end(), 0); }

	ll find(ll a) { return a == id[a] ? a : id[a] = find(id[a]); }

	void uni(ll a, ll b) {
		a = find(a), b = find(b);
		if (a == b) return;
		if (sz[a] < sz[b]) swap(a, b);
		sz[a] += sz[b], id[b] = a;
	}
};

int main(){ _;

    ll n, m; cin >> n >> m;
    v64 vec(n);
    dsu d(n);

    forn(i,0,m){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        d.uni(a,b);
    }

    set<ll> s;

    forn(i,0,n) s.insert(d.find(i));
    cout << s.size()-1 << ln;

    auto it = s.begin();
    forn(i,0,s.size()-1){
        cout << *it+1 << " ";
        it++;
        cout << *it+1 << ln;
    }


    return 0;
}