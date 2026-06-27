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

struct TJ {
    ll n, timer = 0;
    vector<vll>& gg;
    vll tin, low;

    vector<pll> briges;

    TJ(ll n, vector<vll>& g_): n(n), gg(g_){
        tin.assign(n,-1);
        low.resize(n);
        forn(i,0,n) if(tin[i] == -1) dfs(i);
    }

    void dfs(ll v, ll p = -1){
        tin[v] = low[v] = timer++;
        ll ch = 0;

        for(ll to:gg[v]){
            if(to ==p) continue;

            if(tin[to] == -1){
                
                dfs(to, v);
                low[v] = min(low[v], low[to]);

                if(low[to] > tin[v]) briges.push_back({v,to});

                ch++;
            }else{
                low[v] = min(low[v], tin[to]);
            }
        }
    }
};

struct dsu {
    vll id, len;

    dsu(ll n) : id(n), len(n,1) { iota(id.begin(), id.end(), 0);}

    ll find(ll a) { return a == id[a] ? a : id[a] = find(id[a]);}

    bool uni(ll a, ll b){
        a = find(a), b = find(b);
        if(a == b) return false;
        if (len[a] < len[b]) swap(a,b);
        len[a] += len[b], id[b] = a;
    }
};