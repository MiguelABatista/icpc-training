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
    v64 claimed(n,-1);
    v64 time(n,INF);

    function<p64 (ll, ll)> dfs1 = [&](ll u, ll p){        
        if(g[u].size() == 1){
            claimed[u] = u;
            time[u] = 0;
        }

        for(auto& [v, l]: g[u]){
            if(v == p) continue;
            auto [dv, tv] = dfs1(v, u);
            if(tv + l < time[u]){
                time[u] = tv+l;
                claimed[u] = dv;
            }else if(tv + l == time[u]){
                claimed[u] = min(claimed[u], dv);
            }
        }

        claims[claimed[u]]++;
        return (p64){claimed[u],time[u]};  
    };


    function<void (ll, ll)> dfs2 = [&](ll u, ll p){        

        // forn(i,0,n) cout << claimed[i] << " ";; cout << ln;

        for(auto& [leaf, idx]: queries[u]){
            resp[idx] = claims[leaf];
        }

        for(auto& [v, l]: g[u]){
            if(v == p) continue;
            ll claimed_u = claimed[u];     
            ll claimed_v = claimed[v];
            
            ll claims_u = claims[claimed[u]];
            ll claims_v = claims[claimed[v]];

            ll time_u = time[u];
            ll time_v = time[v];

            if(time[v] > time[u] + l || ((time[v] == time[u] + l) and claimed[u] < claimed[v])){
                time[v] = time[u] + l;
                claims[claimed[v]]--;
                claims[claimed[u]]++;
                claimed[v] = claimed[u];
            } 

            ll best_claim = -1;
            ll best_time = INF;

            if(g[u].size() == 1){
                best_claim = u;
                best_time = 0;
            }

            for(auto& [filho, length]: g[u]){
                if(filho == v) continue;
                
                if(time[filho] + length < best_time || ((time[filho] + length == best_time) and claimed[filho] < best_claim)){
                    best_claim = claimed[filho];
                    best_time = time[filho] + length;
                }
            }

            claims[claimed[u]]--;
            claims[best_claim]++;
            claimed[u] = best_claim;
            time[u] = best_time;

            dfs2(v,u);

            time[u] = time_u;
            claimed[u] = claimed_u;
            claims[best_claim]--;
            claims[claimed[u]]++;

            claimed[u] = claimed_u;     
            claimed[v] = claimed_v;
            claims[claimed[u]] = claims_u;
            claims[claimed[v]] = claims_v;
            time[u] = time_u;
            time[v] = time_v;
             
        }

        return;  
    };
    // forn(i,0,n){
    //     claims.assign(n,0);
    //     dfs1(i,-1);
    //     for(auto& [leaf, idx]: queries[i]){
    //         resp[idx] = claims[leaf];
    //     }
    // }
    dfs1(0,-1);
    dfs2(0,-1);
    forn(i,0,q) cout << resp[i] << ln;
    return 0;
}
