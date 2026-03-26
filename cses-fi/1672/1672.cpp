#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

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
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << fixed << setw(3) << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;


// Floyd-Warshall Algorithm
//
// Computes all-pairs shortest paths via DP over intermediate vertices.
// Initialize d[i][j] = edge weight (INF if no edge, 0 on diagonal).
// Returns true if a negative cycle is detected.
//
// complexity: O(N^3), O(N^2)

bool floyd_warshall(ll n, vector<v64>& d) {
    forn(k,0,n)
    forn(i,0,n)
    forn(j,0,n)
        if (d[i][k] != INF && d[k][j] != INF)
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    forn(i,0,n)
        if (d[i][i] < 0) return true;

    return false;
}

int main() {
    _;
    ll n, m, q;
    cin >> n >> m >> q;
    vector<v64> d(n, v64(n, INF));
    forn(i,0,n) d[i][i] = 0;
    forn(i,0,m){   
        ll a, b, c; cin >> a >> b >> c;
        a--;
        b--;
        d[a][b] = min(d[a][b], c);
        d[b][a] = min(d[b][a], c);
    }

    trace(forn(i,0,n){debugv(d[i]);});
    floyd_warshall(n, d);
    trace(forn(i,0,n){debugv(d[i]);});

    while(q--){
        ll a, b; cin >> a >> b;
        a--, b--;
        cout << (d[a][b] == INF ? -1 : d[a][b]) << ln;
    }
    return 0;
}
