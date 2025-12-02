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
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
typedef vector<v64> Tree;
ll temp[5'005];

int main(){
    _;
    ll n, k; cin >> n >> k;

    Tree tree(n);
    forn(i,1,n){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        tree[a].push_back(b); 
        tree[b].push_back(a); 
    }

    vector<v64> dp(n, v64(n+1, 0));

    function<ll (ll, ll)> dfs = [&](ll u, ll p){
        dp[u][1] = 1;
        dp[u][0] = 1;
        ll sz_u = 1;

        for(ll v : tree[u]) if(v != p) {

            ll sz_v = dfs(v, u);
            fill(temp, temp+n+1, 0);
            
            forn(i,1,sz_u+1){
                forn(j,0,sz_v+1){
                    if(temp[i+j] == INF) continue;
                    if(dp[u][i] > INF/dp[v][j]){
                        temp[i+j] = INF;
                        continue;
                    }
                    temp[i+j] += dp[u][i]*dp[v][j];
                }
            }
            sz_u += sz_v;
            forn(i,1,sz_u+1) dp[u][i] = temp[i]; 
        }

        return sz_u;
    };

    dfs(0,-1);
    
    v64 qnt(n+1);

    forn(v,0,n){
        forn(i,1,n+1){
            qnt[i] += dp[v][i];
        }
    }

    ll sum = 0;
    forn(i,0,n+1){
        sum += qnt[i];
        if(sum >= k){
            cout << i << ln;
            return 0;
        }
    }
    cout << -1 << ln;
    return 0;
}