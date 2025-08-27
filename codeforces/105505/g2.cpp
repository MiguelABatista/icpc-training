// Template Skeleton
//
// Sets up fast I/O, aliases, and basic macros for contests.

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
    #define debugp(x) cout << __LINE__ << ": " << #x << " = " << (x).first << " " << (x).second << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
    #define debugp(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;


int main(){
    _;
    ll n; cin >> n;
    vector<vector<p64>> g(n);

    forn(i,0,n-1){
        ll a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({b,c});
        g[b].push_back({a,c});
    }
    
    ll q; cin >> q;
    vector<vector<p64>> queries(n);
    
    forn(i,0,q){
        ll l, t;
        cin >> l >> t;
        l--; t--;
        queries[t].push_back({l,i});
    }
    
    v64 resp(q,0);

    v64 claims(n,0);

    function<p64 (ll, ll)> dfs1 = [&](ll u, ll p){        

        ll dono = -1;
        ll tempo = INF;

        if(g[u].size() == 1){
            dono = u;
            tempo = 0;
        }

        for(auto& [v, l]: g[u]){
            if(v == p) continue;
            auto [dv, tv] = dfs1(v, u);
            if(tv + l < tempo){
                tempo = tv+l;
                dono = dv;
            }else if(tv + l == tempo){
                dono = min(dono, dv);
            }
        }
        claims[dono]++;
        return (p64){dono,tempo};  
    };

    forn(i,0,n){
        claims.assign(n,0);
        dfs1(i,-1);
        for(auto& [leaf, idx]: queries[i]){
            resp[idx] = claims[leaf];
        }
    }

    forn(i,0,q) cout << resp[i] << ln;
    return 0;
}
