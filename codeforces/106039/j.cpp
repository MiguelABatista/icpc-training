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
const ll MOD = 1'000'000'007;

int main() {
    _;
    ll n, m, s, t; cin >> n >> m >> s >> t;
    s--;
    t--;
    vector<v64> g(n);
    forn (i, 0, m) {
        ll a, b; cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<bool> vis(n);
    v64 dist(n, INF), cnt(n), cnt2(n);

    queue<ll> q;
    vis[s] = true;
    dist[s] = 0;
    q.push(s);
    cnt[s] = 1;

    while (!q.empty()) {
        auto u = q.front();
        q.pop();

        for (auto v : g[u]) {
            if (!vis[v]) {
                vis[v] = true;
                dist[v] = dist[u] + 1;
                cnt[v] = cnt[u];
                q.push(v);
            } else if (dist[v] == dist[u] + 1) {
                cnt[v] = (cnt[v] + cnt[u])%MOD;
            }
        }
    }

    vis.assign(n, false);
    vis[s] = true;
    q.push(s);
    cnt2[s] = 0;

    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        ll resp = 0;
        ll d_u = dist[u];

        for (auto v : g[u]) {
            if(dist[v] == d_u-1){
                resp = (resp+cnt2[v])%MOD;
            }
            if(dist[v] == d_u){
                resp = (resp+cnt[v])%MOD;
            }

            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }

        cnt2[u] = resp;
    }

#warning Nao esquece do MOD ARROMBADO

    // forn(i, 0, n) cout << cnt[i] << " \n"[i==n-1];
    // forn(i, 0, n) cout << cnt2[i] << " \n"[i==n-1];
    // forn(i, 0, n) cout << dist[i] << " \n"[i==n-1];
    cout << cnt2[t] << ln;
    return 0; 
}
