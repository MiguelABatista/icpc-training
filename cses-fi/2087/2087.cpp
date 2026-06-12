#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Divide and Conquer DP Optimization
//
// Optimizes DP transitions with quadrangle inequality/monge-like structure using divide-and-conquer over optimal decision points.
//
// complexity: O(K N log N) with O(1) cost, O(N)

vector<vll> dp; // dp[n+1][2]

vll vec;
vector<vll> cost;

void prep(){
    ll n = sz(vec);
    cost.resize(n, vll(n,0));
    vll acc(n);
    vll indo(n), vindo(n);
    vll accindo(n), accvindo(n);

    forn(i,0,n){
        indo[i] = (i+1)*vec[i];
        vindo[i] = (n-i)*vec[i];
        acc[i] = (vec[i] + (i == 0 ? 0 : acc[i-1]));
        
        accindo[i] = (indo[i] + (i == 0 ? 0 : accindo[i-1]));
        accvindo[i] = (vindo[i] + (i == 0 ? 0 : accvindo[i-1]));
    }
    
    auto sum = [](ll l, ll r, vll& v){
        return v[r] - (l == 0 ? 0 : v[l-1]);
    };
    debugv(acc);
    forn(x,0,n){
        forn(y,x+1,n){
            // suponha que o otimo no ponto k 
            // sse (acc[k] - acc[x-1]) <= tot - (acc[k]-acc[x-1]) vale dar um papsso 
            // sse 2acc[j] <= tot
            // sse acc[j] <= tot/2
            // e a resposta é 3vec[x] + 2vec[x+1] + vec[x+2] + 0vec[k] + vec[x+4] + 2vec[x+5]
//  (k-x)vec[x] + (k-(x+1))vec[x+1] + (k-(x+2)vec[x+2] + 0vec[k] + ((x+4) - k)vec[x+4] + ((x+5) - k)vec[x+5]
//  (k-x)vec[x] + (k-(x+1))vec[x+1] + (k-(x+2)vec[x+2] + 0vec[k] + ((x+4) - k)vec[x+4] + ((x+5) - k)vec[x+5]
            ll tot = acc[y] - (x == 0 ? 0 : acc[x-1]);
            ll k = (ll)(upper_bound(acc.begin() + x, acc.begin()+y, tot/2) - acc.begin());
            trace(cout << x << " " << y << " " << k << " " << tot << ln;)
            cost[x][y] = (k-x)*sum(x,k,acc) - k*sum(x,k, accvindo) + k*sum(k,y, accindo) - (y-k)*sum(k,y,acc);
        }
    }

    trace(
        forn(i,0,n){
            forn(j,0,n) cout << setw(2) << cost[i][j] << " ";
            cout << ln;
        }
    )
}

void solve(ll k, ll l, ll r, ll lk, ll rk) {
    if (l > r) return;
    ll m = (l+r)/2, p = -1;
    auto& ans = dp[m][k&1] = INF;
    for (ll i = max(m, lk); i <= rk; i++) {
        ll at = dp[i+1][~k&1] + cost[m][i];
        if (at < ans) ans = at, p = i;
    }
    solve(k, l, m-1, lk, p), solve(k, m+1, r, p, rk);
}

ll dnc(ll n, ll k) {
    dp[n][0] = dp[n][1] = 0;
    forn(i,0,n) dp[i][0] = INF;
    forn(i,1,k+1) solve(i, 0, n-i, 0, n-i);
    return dp[0][k&1];
}


int main() {
    _;
    ll n, k; cin >> n >> k;
    vec.resize(n);
    forn(i,0,n) cin >> vec[i];
    prep();
    return 0;
}
