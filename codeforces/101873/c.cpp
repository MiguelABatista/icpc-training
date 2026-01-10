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

#define debugv(v) trace({cout << #v": "; for (auto u : v) cout<< u << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _;
    ll x; cin >> x;
    ll n, m, t;
    cin >> n >> m >> t;
    vector<v64> g(n);

    forn(i,0,m){
        ll a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<p64> tc(n);

    forn(i,0,n) cin >> tc[i].first >> tc[i].second;
    
    vector<v64> dp(x+1, v64(n,INF));

    dp[tc[0].first][0] = tc[0].second;

    forn(i,1,x+1){
        forn(u,0,n){
            ll curr = dp[i][u];
            
            if(i >= tc[u].first){
                curr = min(curr, dp[i-tc[u].first][u] + tc[u].second);
            }

            ll aux = tc[u].first+t;
            
            if(i >= aux){
                for(ll v: g[u]){
                    curr = min(curr, dp[i-aux][v] + tc[u].second);    
                }
            }
            dp[i][u] = curr;
        }
    } 

    forn(i,0,x+1) debugv(dp[i]);
    if(dp[x][0] >= INF){
        cout << "It is a trap." << ln;
    }else{
        cout << dp[x][0] << ln;
    }
    return 0;
}