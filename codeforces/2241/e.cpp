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

set<ll> sqnum;

void prep(){
    forn(i,0,1010) sqnum.insert(i*i);    
}

bool is_sq(ll x){
    return sqnum.find(x) != sqnum.end();
}

ll func(vll v, ll s){
    ll resp = (s*(s-1)*(s-2))/6;
    for(ll x: v) resp -= (x*(x-1)*(x-2))/6;
    for(ll x: v) resp -= ((x*(x-1))/2) * (s-x);
    return resp;
}

void solve(){
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    vector<vll> g(n);
    forn(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vll sub(n);
    vll pai(n);

    function<void (ll, ll)> dfs = [&](ll u, ll p){
        sub[u] = 1;
        pai[u] = p;
        for(ll v : g[u]){
            if(v == p) continue;
            dfs(v,u);
            sub[u] += sub[v];
        }
    };

    dfs(0, -1);
    ll resp = 0;

    forn(u,0,n) if(is_sq(vec[u])){
        vll ve;
        for(ll v: g[u]) if(v != pai[u]) ve.push_back(sub[v]);
        ve.push_back(n-sub[u]);
        // sem usar o u
        resp += func(ve, n-1);

        // usando u e dois abaixo
        ll ans = (sub[u]-1)*(sub[u]-2)/2;
        for(ll v: g[u]) if(v != pai[u]) ans -= (sub[v])*(sub[v]-1)/2;
        resp += ans;

        // usando u um abaixo, e outro acima
        resp += (sub[u]-1)*(n-sub[u]);
    }
    
    cout << resp << ln;
}

int main() {
    _;
    prep();
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
