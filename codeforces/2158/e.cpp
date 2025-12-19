#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Order-Statistic Tree (PBDS)
//
// Wraps __gnu_pbds tree to support order_of_key and find_by_order operations on a sorted set.
//
// complexity: O(log N) per op, O(N)

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

#define ordered_set tree<ver, null_type,less<ver>, rb_tree_tag,tree_order_statistics_node_update> 

struct ver
{
    ll ingrau = 0;
    ll i, j;
    bool operator < (const ver p) const {
		if (ingrau != p.ingrau) return ingrau < p.ingrau;
		if(i != p.i) return i < p.i;
        return j < p.j;
	}
};

void solve(){
    ll n, m; cin >> n >> m;
    vector<v64> mat(n, v64(m));
    vector<v64> g(n, v64(m));
    ordered_set s;
    forn(i,0,n) forn(j,0,m) cin >> mat[i][j];

    forn(i,0,n) forn(j,0,m){
        ll deg = 0;
        if(i > 0 && mat[i-1][j] <= mat[i][j]) deg++;
        if(j > 0 && mat[i][j-1] <= mat[i][j]) deg++;
        if(i < n-1 && mat[i+1][j] <= mat[i][j]) deg++;
        if(j < m-1 && mat[i][j+1] <= mat[i][j]) deg++;
        g[i][j] = deg;
        s.insert({deg, i, j});
    }

    forn(i,0,n) debugv(mat[i]);
    forn(i,0,n) debugv(g[i]);
    trace(
        for(auto key : s){
            cout << key.ingrau << " " << key.i << " " << key.j << ln;
        }
    );
    cout << s.order_of_key({0, INF, INF}) << ln;

    ll q; cin >> q;
    while(q--){
        ll a, b, c; 
        cin >> a >> b >> c;
    }
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}