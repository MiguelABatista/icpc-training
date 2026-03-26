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
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Centroid Tree
//
// Constroi a centroid tree
// p[i] eh o pai de i na centroid-tree
// dist[i][k] = distancia na arvore original entre i
// e o k-esimo ancestral na arvore da centroid
//
// O(n log(n)) de tempo e memoria

const ll MAX = 100'005;
vector<v64> g(MAX), dist(MAX);
v64 siz(MAX), rem(MAX), p(MAX);

ll dfs_sz(ll i, ll l=-1) {
    siz[i] = 1;
    for (ll j : g[i]) if (j != l && !rem[j]) siz[i] += dfs_sz(j, i);
    return siz[i];
}

ll centroid(ll i, ll l, ll size) {
    for (ll j : g[i]) if (j != l && !rem[j] && siz[j] > size / 2)
        return centroid(j, i, size);
    return i;
}

void dfs_dist(ll i, ll l, ll d=0) {
    dist[i].push_back(d);
    for (ll j : g[i]) if (j != l && !rem[j])
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

int main() {
    _;

    ll n; cin >> n;

    forn(i,0,n-1){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    build(n);

    vector<p64> dp(n, {INF, INF});
    v64 resp(n, -1);

    for(ll i = n-1; i >= 0; i--){
        p64 best = {INF, INF};

        ll pai = i;
        ll cnt = 0;

        while(pai != -1){
            p64 prox = {dp[pai].first + dist[i][cnt], dp[pai].second};
            if(prox < best) best = prox;

            debug(dist[i][cnt]);
            dp[pai] = min(dp[pai], {dist[i][cnt], i});
            cnt++;
            pai = p[pai];
        }   
        resp[i] = best.second; 
    }

    trace(
        forn(i,0,n) cout << dp[i].first << " " << dp[i].second << ln;
    ) 
    resp[n-1] = n-1;
    forn(i,0,n) cout << resp[i]+1 << " \n"[i==n-1];

    return 0;
}
