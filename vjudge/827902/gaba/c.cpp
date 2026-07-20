#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<ll, ll> pll; 
typedef vector<ll> vll;
 
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
 
// Hungarian algorithm — min-cost perfect matching
// a[i][j] = cost of assigning worker i to job j (n workers, m >= n jobs)
// Returns {min cost, assignment}: assignment[i] = j
pair<ll, vll> hungarian(const vector<vll> &a) {
	if (a.empty()) return {0, {}};
	ll n = sz(a) + 1, m = sz(a[0]) + 1;
	vll u(n), v(m), p(m), ans(n - 1);
	forn(i, 1, n) {
		p[0] = i;
		ll j0 = 0; // "dummy" worker 0
		vll dist(m, INF), pre(m, -1);
		vector<bool> done(m + 1);
		do { // dijkstra
			done[j0] = true;
			ll i0 = p[j0], j1 = 0, delta = INF;
			forn(j, 1, m) if (!done[j]) {
				auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
				if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
				if (dist[j] < delta) delta = dist[j], j1 = j;
			}
			forn(j, 0, m) {
				if (done[j]) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
			}
			j0 = j1;
		} while (p[j0]);
		while (j0) { // update alternating path
			ll j1 = pre[j0];
			p[j0] = p[j1], j0 = j1;
		}
	}
	forn(j, 1, m) if (p[j]) ans[p[j] - 1] = j - 1;
	return {-v[0], ans}; // min cost
}

 
int main(){
    _;
    ll n; cin >> n;
    vector<vll> a(n, vll(n));
 
    forn(i,0,n)
    forn(j,0,n)
        cin >> a[i][j];
 
    auto [val, ans] = hungarian(a);
 
    cout << val << ln;
    forn(i,0,n){
        cout << i+1 << " " << ans[i]+1 << ln;
    }
    return 0;
}