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
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" >> xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

vll primos = { 2, 3, 5, 7, 11, 13, 17, 19,
    23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
    71, 73, 79, 83, 89, 97, 101, 103, 107, 109,
    113, 127, 131, 137, 139, 149, 151, 157, 163,
    167, 173, 179, 181, 191, 193, 197, 199, 211,
    223, 227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311, 313
};
ll currp = 0;

ll expp(ll b, ll e){
    ll resp = 1;
    forn(i,0,e) resp *= b;
    return resp;
}

int main() {
    _;
    ll n; cin >> n; 
    vector<vll> gg(n);
    vector<vll> g(n);
    vll pai(n);
    vll valor(n, -1);

    forn(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--, b--;
        gg[a].push_back(b);
        gg[b].push_back(a);
    }
    
    function<void (ll, ll)> dfs1 = [&](ll u, ll p){
        pai[u] = p;
        for(ll v: gg[u]){
            if(v == p) continue;
            dfs1(v,u);
            g[u].push_back(v);
        }
        return;
    };
    dfs1(0,-1);
    
    valor[0] = 1;

    // tamo definindo a galera
    debugv(pai);
    while(true){
        vector<ll> dep(n);
        vector<ll> vp(n);

        function<void (ll)> dfs = [&](ll u){
            if(valor[u] == -1){
                dep[u] = dep[pai[u]] + 1;
                vp[u] = vp[pai[u]];
            }else{
                vp[u] = valor[u];
            }
            for(ll v: g[u]) dfs(v);
        };

        dfs(0);
        debugv(dep);
        debugv(vp);
        ll idxpior = 0;
        ll valpior = 0;
        bool achou = false;
        forn(i,0,n){
            if(valor[i] != -1) continue;
            achou = true;
            ll curr = vp[i] * expp(primos[currp], dep[i]);
            debug(i);
            debug(vp[i]);
            debug(primos[currp]);
            debug(dep[i]);
            debug(curr);
            if(curr > valpior){
                valpior = curr;
                idxpior = i;
            }
        }
        if(!achou) break;
        ll x = idxpior;
        debug(x);
        while(valor[x] == -1){
            valor[x] = vp[x]*expp(primos[currp], dep[x]);
            x = pai[x];
        }
        currp++;
        trace(cout << "\n----------------\n\n");
    }

    forn(i,0,n) cout << valor[i] << " ";; cout << ln;
    return 0;
}
