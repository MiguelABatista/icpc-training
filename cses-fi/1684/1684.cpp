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

// 2-SAT
//
// solve() retorna um par, o first fala se eh possivel
// atribuir, o second fala se cada variavel eh verdadeira
//
// O(|V|+|E|) = O(#variaveis + #restricoes)

struct sat {
    ll n, tot;
    vector<v64> g;
    v64 vis, comp, id, ans;
    v64 s;

    sat() {}
    sat(ll n_) : n(n_), tot(n), g(2*n) {}

    ll dfs(ll i, ll& t) {
        ll lo = id[i] = t++;
        s.push_back(i), vis[i] = 2;
        for (ll j : g[i]) {
            if (!vis[j]) lo = min(lo, dfs(j, t));
            else if (vis[j] == 2) lo = min(lo, id[j]);
        }
        if (lo == id[i]) while (1) {
            ll u = s.back(); s.pop_back();
            vis[u] = 1, comp[u] = i;
            if ((u>>1) < n && ans[u>>1] == -1) ans[u>>1] = ~u&1;
            if (u == i) break;
        }
        return lo;
    }

    void add_impl(ll x, ll y) { // x -> y = !x ou y
        x = x >= 0 ? 2*x : -2*x-1;
        y = y >= 0 ? 2*y : -2*y-1;
        g[x].push_back(y);
        g[y^1].push_back(x^1);
    }
    void add_cl(ll x, ll y) { // x ou y
        add_impl(~x, y);
    }
    void add_xor(ll x, ll y) { // x xor y
        add_cl(x, y), add_cl(~x, ~y);
    }
    void add_eq(ll x, ll y) { // x = y
        add_xor(~x, y);
    }
    void add_true(ll x) { // x = T
        add_impl(~x, x);
    }
    void at_most_one(v64 v) { // no max um verdadeiro
        g.resize(2*(tot+sz(v)));
        for (ll i = 0; i < sz(v); i++) {
            add_impl(tot+i, ~v[i]);
            if (i) {
                add_impl(tot+i, tot+i-1);
                add_impl(v[i], tot+i-1);
            }
        }
        tot += sz(v);
    }

    pair<bool, v64> solve() {
        ans = v64(n, -1);
        ll t = 0;
        vis = comp = id = v64(2*tot, 0);
        for (ll i = 0; i < 2*tot; i++) if (!vis[i]) dfs(i, t);
        for (ll i = 0; i < tot; i++)
            if (comp[2*i] == comp[2*i+1]) return {false, {}};
        return {true, ans};
    }
};

int main() {
    _;
    ll n, m; cin >> n >> m;
    sat s(m);
    forn(i,0,n){
        char c1, c2;
        ll s1, s2;
        cin >> c1 >> s1 >> c2 >> s2;
        s1--; s2--;
        if(c1 == '-') s1 = ~s1; 
        if(c2 == '-') s2 = ~s2; 
        s.add_cl(s1, s2);
    }
    auto [b,v] = s.solve();
    if(!b){
        cout << "IMPOSSIBLE" << ln;
        return 0;
    }
    debugv(v);
    forn(i,0,m){
        cout << (v[i] ? '+' : '-') << " \n"[i==m-1];
    }
    return 0;
}
