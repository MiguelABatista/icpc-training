#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for (ll i=(s); i<(e); i++)
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
#define debugv(v) trace(cout << #v ": "; for(auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n, m, k; cin >> n >> m >> k;
    vector<string> street(n);
    vll obstruct(m, n+1-k);

    forn(i, 0, n) cin >> street[i];

    for(ll i = n-1; i>= 0; i--){
        forn(j, 0, m){
            debug(i);
            debug(j);
            debug(obstruct[j]);

            if(street[i][j] == 'x') obstruct[j] = i+1-k;
            if(i>= obstruct[j]) street[i][j] = 'x';
        }
    }

    forn(i, 0, n) debug(street[i]);
 
    vector<vll> g(n*m);
    vll depth(n*m);

    forn(i, 0, n)
    forn(j, 0, m){
        if(street[i][j] == 'X') continue;
        if(j > 0 && street[i][j-1] != 'x') g[i*m + j].push_back(i*m+j-1);
        if(j < m-1 && street[i][j+1] != 'x') g[i*m + j].push_back(i*m+j+1);
        if(i < n-1 && street[i+1][j] != 'x') g[i*m + j].push_back((i+1)*m+j);
        depth[i*m + j] = i;
    }

    forn(i, 0, n*m){
        debugv(g[i]);
    }

    ll max_depth = 0;

    vector<bool> visited(n*m, false);
    function<void (ll)> dfs = [&](ll curr){
        debug(curr);
        if(visited[curr]) return;
        visited[curr] = true;

        max_depth = max(max_depth, depth[curr]); 

        for(auto next : g[curr]) dfs(next);
    };
 
    dfs(0);

    cout << max_depth+k << ln;
}

int main(){
    _; ll t; cin >> t;
    while(t--) solve();
    return 0;
}