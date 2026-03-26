#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debugp(v) trace({cout << #v": "; for (auto x : v) cout<< x.first << ":" << x.second << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll resolve(vector<p64>& vec){
    ll n = sz(vec);
    
    debug(n);
    v64 dp1(n); // sem n-1
    dp1[0] = vec[0].first; 
    dp1[1] = max(vec[0].first + vec[1].second, vec[1].first+vec[0].second);
    
    forn(i,2,n-1){
        dp1[i] = max(dp1[i-1]+vec[i].second, dp1[i-2] + vec[i].first);
    }
    
    if(n == 2) return dp1[n-1];

    v64 dp2(n); // sem 0
    dp2[1] = vec[1].first;
    dp2[2] = max(vec[1].first + vec[2].second, vec[2].first+vec[1].second);
    forn(i,3,n){
        dp2[i] = max(dp2[i-1]+vec[i].second, dp2[i-2] + vec[i].first);
    }

    return max(dp1[n-2], dp2[n-1]);
}


void solve(){
    ll n; cin >> n;
    v64 nxt(n);

    vector<v64> g(n);
    forn(i,0,n){
        cin >> nxt[i];
        nxt[i]--;
        g[nxt[i]].push_back(i);
    }

    v64 ciclo(n,-1);
    v64 visitado(n,INF);
    ll curr_ciclo = 0;
    ll tempo = 0;

    function<void (ll)> popula_ciclo = [&](ll u){
        if(visitado[u] < tempo) return;
        if(visitado[u] == tempo){
            ciclo[u] = curr_ciclo;
            ll prox = nxt[u];
            while(prox != u){
                ciclo[prox] = curr_ciclo;
                prox = nxt[prox];
            }
            curr_ciclo++;
            return;
        }
        visitado[u] = tempo;
        popula_ciclo(nxt[u]);
    };

    forn(i,0,n){
        if(visitado[i] < INF) continue;
        popula_ciclo(i);
        tempo++; 
    }

    debugv(ciclo);

    vector<p64> dp(n, {-1,-1}); // com, sem
    
    function<p64 (ll)> popula_dp = [&](ll u){
        if(dp[u].first != -1) return dp[u];
        ll dp_com = 1;
        ll dp_sem = 0;

        for(ll v : g[u]){
            if(ciclo[v] != -1) continue;
            p64 dp_f = popula_dp(v);
            dp_com += dp_f.second;
            dp_sem += max(dp_f.first, dp_f.second);
        }   

        dp[u] = {dp_com, dp_sem};
        return dp[u];
    };

    forn(i,0,n){
        if(dp[i].first != -1) continue;
        popula_dp(i);
    }

    debugp(dp);

    vector<vector<p64>> to_solve(curr_ciclo);

    set<ll> valid_cicles;
    forn(i,0,curr_ciclo) valid_cicles.insert(i);

    forn(i,0,n){
        if(!valid_cicles.count(ciclo[i])) continue;
        
        ll c = ciclo[i];
        vector<p64>& v = to_solve[c];
        ll u = nxt[i];
        v.push_back(dp[i]);
        while(u != i){
            v.push_back(dp[u]);
            u = nxt[u];
        }
        valid_cicles.erase(ciclo[i]);
    }

    forn(i,0,curr_ciclo){
        debug(i);
        debugp(to_solve[i]);
    }


    ll resp = 0;
    for(auto& v: to_solve) resp += resolve(v);
    cout << n-resp << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--){
        solve();
    }

    return 0;
}