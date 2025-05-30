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

int main(){
    _; 
    ll n, m; cin >> n >> m;

    vector<vector<ll>> g(n);
    priority_queue<pair<ll,ll>> pq;

    vector<ll> grau_efetivo(n);
    forn(i, 0, m){
        ll a, b; cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    forn(i, 0, n){
        pq.push({g[i].size(),i});
        grau_efetivo[i] = g[i].size();
    }

    // for(auto x : ord_grau) cout << x.second << " ";
    // cout << ln;

    ll vert = n;
    vector<ll> in_complete(n, -1);
    // -1 ainda n visitado
    // 0 clique
    // 1 independete

    while(!pq.empty()){
        auto it = pq.top();
        pq.pop();
        ll ind = it.second;

        if(in_complete[ind] == 1) continue;
        
        assert(grau_efetivo[ind] <= vert - 1);

        if(grau_efetivo[ind] >= vert-1){
            debug(ind);
            cout << "YES" << ln;
            return 0;
        }    

        if(in_complete[ind] == 0){
            cout << "NO" << ln;
            return 0;
        }
        
        for(auto y : g[ind]){
            in_complete[y] = 0;
            grau_efetivo[y]--;
            pq.push({grau_efetivo[y], y});
        }

        vert--;
    }

    cout << "NO" << ln;
    
    return 0;
}