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

#define debug(u) trace(cout << __LINE__ << ": " << #u " = " << u << ln)
#define debugv(v) trace(cout << __LINE__ << ": " << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll LOG = 33;


int main() {
    _;
    
    ll n; cin >> n;
    vector<v64> nxt(LOG, v64(n));
    vector<v64> g(n);
    forn(i,0,n){
        cin >> nxt[0][i];
        nxt[0][i]--;
        g[nxt[0][i]].push_back(i);
    }

    forn(j,1,LOG){
        forn(i,0,n){
            nxt[j][i] = nxt[j-1][nxt[j-1][i]]; 
        }
    }

    auto anda = [&](ll x, ll k){
        ll j = 0;
        while(k){
            if(k&1) x = nxt[j][x];
            k >>= 1;j++;
        }
        return x;
    };

    v64 cic(n, -1);
    v64 cicpos(n, -1);
    v64 prof(n, -1);
    v64 vis(n, -1);

    ll nxt_cic = 0;
    ll ini = -1;
    function<ll (ll)> dfs = [&](ll u){
        debug(u);
        vis[u] = 0;
        ll v = nxt[0][u];
        if(u == v){
            prof[u] = 0;
            cic[u] = nxt_cic++;
            cicpos[u] = 0;
            vis[u] = 1;
            return 1ll;
        }
        if(vis[v] == 0){
            ini = v;
            prof[u] = 0;
            cic[u] = nxt_cic++;
            cicpos[u] = 0;
            vis[u] = 1;
            return 0ll;
        }
        if(vis[v] == 1){
            prof[u] = prof[v]+1;
            cic[u] = cic[v];
            vis[u] = 1;
            return 1ll;
        }
        ll r = dfs(v);
        if(r == 1){
            prof[u] = prof[v]+1;
            cic[u] = cic[v];
            vis[u] = 1;
            return 1ll;   
        }
        if(r == 0){
            prof[u] = 0;
            cic[u] = cic[v];
            cicpos[u] = cicpos[v]+1;
            vis[u] = 1;
            return (ll)(u == ini);
        }
        return -INF;
    };

    
    forn(i,0,n){
        if(vis[i] == -1) dfs(i);
    }

    v64 cicsz(nxt_cic);
    forn(i,0,n) cicsz[cic[i]] = max(cicsz[cic[i]], cicpos[i]+1);
    forn(i,0,n) if(cicpos[i] != -1) cicpos[i] = cicsz[cic[i]] - cicpos[i];

    forn(i,0,n){
        cout << prof[i] + cicsz[cic[i]] << " \n"[i==n-1];
    }

    return 0;
}
 