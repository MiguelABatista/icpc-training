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

void solve(){
    ll n, k; cin >> n >> k;

    vector<v64> g(n);
    forn(i,0,n-1){
        ll a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    v64 sub(n);
    v64 pai(n);
    
    function<void (ll ,ll)> dfs = [&](ll u, ll p){
        ll resp = 1;
        pai[u] = p;
        for(ll v : g[u]){
            if(v == p) continue;
            dfs(v,u);
            resp += sub[v];
        }
        sub[u] = resp;
    };

    dfs(0, -1);

    ll resp = 0;
    forn(u,0,n){
        ll curr = n;
        ll tot = 0;

        for(ll v: g[u]){
            if(v == pai[u]) continue;
            tot += sub[v];
            
            if(sub[v] > n - k) curr -= sub[v];
        }
        
        if(pai[u] != -1){
            ll last = n - (tot+1);
            if(last > n-k) curr -= last;
        } 
        resp += curr;
    }

    cout << resp << ln;
    trace(cout << "------------\n\n");
}

int main() {
    _;
    ll t; cin >> t; 
    while(t--) solve();

    return 0;
}
