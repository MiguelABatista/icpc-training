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
const vector<pll> vis = {{1,1}, {-1,1}, {1,-1}, {-1,-1}};

ll n;
ll tonum(ll x, ll y){
    return x*(n-1) + y;
}

int main() {
    _;
    cin >> n;
    vector<string> mat(n);
    forn(i,0,n) cin >> mat[i];
    vector<vll> g(n*n);

    forn(i,0,n) forn(j,0,n){
        if(mat[i][j] != 'P') continue;

        for(auto [a, b] : vis){
            ll ni = i + a;
            ll nj = j + b;
            if(ni < 0 || ni >= n) continue;
            if(nj < 0 || nj >= n) continue;
            if(mat[ni][nj] != '.') continue;

            for(auto [x,y] : vis){
                ll pi = ni + x;
                ll pj = nj + y;
                if(pi < 0 || pi >= n) continue;
                if(pj < 0 || pj >= n) continue;
                if(mat[pi][pj] != 'P') continue;
                ll idx1 = n*i + j;
                ll idx2 = n*pi + pj;
                g[idx1].push_back(idx2);
                g[idx2].push_back(idx1);
            }
        }
    }

    forn(i,0,n*n){
        sort(g[i].begin(), g[i].end());
        g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
        debug(i);
        debugv(g[i]);
    }
    return 0;
    // grafo das pessoas pretas ta montado
    vll visitados(n*n);

    function<ll (ll)> dfs = [&](ll u){
        visitados[u] = true;

        ll resp = 0;
        for(ll v: g[u]) if(!visitados[v]){
            resp = max(resp, dfs(v));
        }
        visitados[u] = false;
        return resp+1;
    };

    ll resp = 0;
    forn(i,0,n) forn(j,0,n){
        if(mat[i][j] != 'B') continue;
        for(auto [a, b] : vis){
            ll ni = i + a;
            ll nj = j + b;
            if(ni < 0 || ni >= n) continue;
            if(nj < 0 || nj >= n) continue;
            if(mat[ni][nj] != 'P') continue;

            resp = max(dfs(n*ni + nj), resp);
        }
    }
    cout << resp << ln;
    return 0;
}
