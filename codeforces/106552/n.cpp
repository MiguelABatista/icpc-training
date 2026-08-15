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
        if(mat[i][j] != '.') continue;

        for(auto [a, b] : vis){
            ll mi = i + a;
            ll mj = j + b;
            ll ni = i + 2*a;
            ll nj = j + 2*b;
            if(ni < 0 || ni >= n) continue;
            if(nj < 0 || nj >= n) continue;
            if(mat[mi][mj] != 'P') continue;
            if(mat[ni][nj] != '.') continue;
            ll idx1 = n*i + j;
            ll idx2 = n*ni + nj;
            g[idx1].push_back(idx2);
        }
    }

    // forn(i,0,n*n){
    //     debug(i);
    //     debugv(g[i]);
    // }

    // grafo das pessoas pretas ta montado
    set<pll> s;
    ll nn = n*n;
    vector<bool> aux(nn*nn);

    function<ll (ll)> dfs = [&](ll u){
        trace(cout << u << " " << u/n << ":" << u%n << ln;)

        ll resp = 0;
        for(ll v: g[u]) {
            if(aux[u*nn+v]) continue;
            aux[u*nn+v] = 1;
            aux[v*nn+u] = 1;
            // if(s.count({u, v})) continue;
            // s.insert({u, v});
            // s.insert({v, u});
            resp = max(resp, dfs(v));
            aux[u*nn+v] = 0;
            aux[v*nn+u] = 0;
            // s.erase({u, v});
            // s.erase({v, u});
        }
        return resp+1;
    };

    auto addB = [&](ll i, ll j){
        for(auto [a, b] : vis){
            ll mi = i + a;
            ll mj = j + b;
            ll ni = i + 2*a;
            ll nj = j + 2*b;
            if(ni < 0 || ni >= n) continue;
            if(nj < 0 || nj >= n) continue;
            if(mat[mi][mj] != 'P') continue;
            if(mat[ni][nj] != '.') continue;
            ll idx1 = n*i + j;
            ll idx2 = n*ni + nj;
            g[idx1].push_back(idx2);
            g[idx2].push_back(idx1);
        }
    };

    auto eraseB = [&](ll i, ll j){
        for(auto [a, b] : vis){
            ll mi = i + a;
            ll mj = j + b;
            ll ni = i + 2*a;
            ll nj = j + 2*b;
            if(ni < 0 || ni >= n) continue;
            if(nj < 0 || nj >= n) continue;
            if(mat[mi][mj] != 'P') continue;
            if(mat[ni][nj] != '.') continue;
            ll idx1 = n*i + j;
            ll idx2 = n*ni + nj;
            g[idx1].pop_back();
            g[idx2].pop_back();
        }
    };

    ll resp = 0;
    forn(i,0,n) forn(j,0,n){
        if(mat[i][j] != 'B') continue;

        for(auto [a, b] : vis){
            ll mi = i + a;
            ll mj = j + b;
            ll ni = i + 2*a;
            ll nj = j + 2*b;
            if(ni < 0 || ni >= n) continue;
            if(nj < 0 || nj >= n) continue;
            if(mat[mi][mj] != 'P') continue;
            if(mat[ni][nj] != '.') continue;
            addB(i,j);
            resp = max(resp, dfs(n*i+j));
            eraseB(i,j);
        } 
    }
    if(resp > 0) resp--;
    cout << resp << ln;
    return 0;
}
