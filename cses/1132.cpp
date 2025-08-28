#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;


vector<v64> g;




void bfs(ll s, v64& d){
    queue<p64> q;
    q.push({0,s});
    d[s] = 0;
    while(!q.empty()){
        auto [dist, v] = q.front();
        q.pop();
        d[v] = dist;
        for(ll u : g[v]){
            if(d[u] != INF) continue;
            q.push({dist+1, u});
        }
    }
}

int main(){
    _;
    ll n; cin >> n;
    g.resize(n);
    v64 d0(n, INF);
    v64 d1(n, INF);
    v64 d2(n, INF);

    forn(i,1,n){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    bfs(0, d0);
    ll longe = -1;
    ll diam1 = 0;
    forn(i,0,n){
        if(d0[i] > longe){
            diam1 = i;
            longe = d0[i];
        }
    }
    bfs(diam1, d1);
    longe = -1;    
    ll diam2 = 0;
    forn(i,0,n){
        if(d1[i] > longe){
            diam2 = i;
            longe = d1[i];
        }
    }
    bfs(diam2, d2);

    forn(i,0,n) cout << max(d1[i], d2[i]) << " ";; cout << ln;
    return 0;
}
