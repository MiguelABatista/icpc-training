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
const ll MOD = 1'000'000'007;


int main() {
    _;
    ll n, q; cin >> n >> q;
    vector<vll> g(n);

    map<pll, ll> pesos;
    vector<tuple<ll,ll,ll>> edg(n-1);

    forn(i,0,n-1){
        ll a, b, w; cin >> a >> b >> w;
        a--, b--;
        edg[i] = {a,b,w};
        pesos[{a,b}] = w; 
        pesos[{b,a}] = w;
        g[a].push_back(b); 
        g[b].push_back(a); 
    }

    vll pai(n);
    vll sub(n);
    function<void (ll, ll)> dfs = [&](ll u, ll p){
        pai[u] = p;
        ll resp = 1;
        for(ll v: g[u]){
            if(v == p) continue;
            dfs(v,u);
            resp += sub[v];
        }
        sub[u] = resp;
    };

    dfs(0,-1);
    
    forn(i,0,n-1){
        auto[a,b,w] = edg[i];
        if(b == pai[a]) continue;
        edg[i] = {b,a, w};
        // edg[i] = filho pai peso
    }
    ll resp = 0;
    forn(i,0,n-1){
        auto[a,b,w] = edg[i];
        resp = (resp + w*( (sub[a]*(n-sub[a]))%MOD ))%MOD;
    }
    
    while(q--){
        ll idx, nw; cin >> idx >> nw;
        idx--;
        auto[a,b,w] = edg[idx];
        resp = ((resp - w*( (sub[a]*(n-sub[a]))%MOD ))%MOD + MOD)%MOD;
        resp = (resp + nw*( (sub[a]*(n-sub[a]))%MOD ))%MOD;
        edg[idx] = {a,b, nw};
        cout << resp << ln;
    }

    return 0;
}
