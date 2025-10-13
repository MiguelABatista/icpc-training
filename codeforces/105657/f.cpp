#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void) 0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

vector<bool> visited;

void dfs(ll v, vector<v64> &g, vector<ll> &out){
    visited[v] = true;
    for(auto u : g[v]) if(!visited[u]) dfs(u, g, out);
    out.push_back(v);
}

pair<v64, v64> scc(vector<v64>& g) {
    ll n = g.size();
    v64 order, roots(n, 0), siz;
    vector<v64> adj_rev(n);
    forn(u, 0, n) for (ll v : g[u]) adj_rev[v].push_back(u);

    visited.assign(n, false);
    forn(i, 0, n) if (!visited[i]) dfs(i, g, order);
    reverse(order.begin(), order.end());

    visited.assign(n, false);
    ll curr_comp = 0;
    for (auto v : order) {
        if(!visited[v]){
            v64 component; dfs(v, adj_rev, component);
            for(auto u : component) roots[u] = curr_comp;
            siz.push_back(component.size());
            curr_comp++;
        }
    }

    return {roots, siz};
}

int mainl() {
    ll n, k, q; cin >> n >> k >> q;
    vector<v64> linhas(k, v64(n));
    vector<v64> g(n);
    forn(i, 0, k) forn(j, 0, n) cin >> linhas[i][j], linhas[i][j]--;

    forn(i, 0, k) 
    forn(j, 1, n) {
        debug(linhas[i][j-1]);
        debug(linhas[i][j]);
        debug(n);
        g[linhas[i][j-1]].push_back(linhas[i][j]);

    }

    auto [roots, siz] = scc(g);

    vector<v64> pfsz(k);
    vector<v64> pfsum(k);

    forn(i, 0, k) {
        v64 prefsz;
        v64 prefsum;
        ll curr = 1;
        forn(j, 1, n) {
            if (roots[linhas[i][j]] == roots[linhas[i][j]]) {
                curr++;
            } else {
                prefsz.push_back(curr);
                prefsum.push_back((curr * (curr-1)) / 2);
                curr = 1;
            }
        }
        prefsz.push_back(curr);
        prefsum.push_back((curr * (curr-1)) / 2);

        forn(j, 1, prefsum.size()) {
            prefsz[i] += prefsz[i-1];
            prefsum[i] += prefsum[i-1];
        }
        pfsz.push_back(move(prefsz));
        pfsum.push_back(move(prefsum));
    }

    function<ll (ll, ll, ll)> solve = [&](ll id, ll l, ll r) {
        ll bottom = upper_bound(pfsz[id].begin(), pfsz[id].end(), l) - pfsz[id].begin();
        ll top = upper_bound(pfsz[id].begin(), pfsz[id].end(), r) - pfsz[id].begin();
        debug(top);
        debug(r);
        if (pfsz[id][top] != r) {
            top--;
        }
        ll mid = pfsum[id][top] - (bottom == 0? 0 : pfsum[id][bottom-1]);
        mid += (bottom - l) * (bottom - l - 1) / 2;
        mid += (r - top) * (r - top - 1) / 2;
        return mid;
    };

    ll vi = 0;
    while (q--) {
        ll id, l , r; cin >> id >> l >> r;
        id = ((id + vi) % k);
        l = ((l + vi) % k);
        r = ((r + vi) % k);

        vi = solve(id, l, r);
        cout << vi << ln;
    }

    
    return 0;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) mainl();
}