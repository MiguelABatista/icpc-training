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
const ll MAXN = 5'005;

ll dp[3][MAXN][MAXN]; // [0 = without dis and without u, 1 = without dis and with u, 2 = with dis][v][amount] 
ll temp0[MAXN];
ll temp1[MAXN];
ll temp2[MAXN];

int main(){
    _;
    ll n, b; cin >> n >> b;
    v64 c(n);
    v64 d(n);
    vector<v64> g(n);

    forn(i,0,n){
        cin >> c[i] >> d[i];
        if(i > 0){
            ll p; cin >> p;
            p--;
            g[i].push_back(p);
            g[p].push_back(i);
        }
    }  

    // [0 = without dis and without u, 1 = without dis and with u, 2 = with dis][v][amount]
    function<ll (ll, ll)> dfs = [&](ll u, ll p){
        ll szu = 1;

        dp[0][u][0] = 0;
        dp[0][u][1] = INF;
        dp[1][u][0] = 0;
        dp[1][u][1] = c[u];
        dp[2][u][0] = 0;
        dp[2][u][1] = d[u];

        for(ll v: g[u]) if(v != p){
            fill(temp0, temp0+MAXN, INF);
            fill(temp1, temp1+MAXN, INF);
            fill(temp2, temp2+MAXN, INF);

            ll szv = dfs(v,u);
            
            forn(i,0,szu){
                forn(j,0,szv){
                    temp0[i+j] = min(temp0[i+j], dp[0][u][i] + dp[0][v][j]); 
                }   
            }

            forn(i,0,szu+szv+1) dp[0][u][i] = temp0[i];
            forn(i,1,szu){
                forn(j,0,szv){
                    ll ans = min(dp[1][u][i] + dp[0][v][j], dp[1][u][i] + dp[1][v][j]);
                    temp1[i+j] = min(temp1[i+j], ans); 
                }   
            }
            forn(i,0,szu+szv) dp[1][u][i] = temp1[i];
            
            forn(i,1,szu){
                forn(j,0,szv){
                    ll ans = INF;
                    ans = min(ans, dp[2][u][i] + dp[2][v][j]); // des nos 2
                    ans = min(ans, dp[2][u][i] + dp[0][v][j]); // des so no u sem v
                    ans = min(ans, dp[2][u][i] + dp[1][v][j]); // des so no u com v
                    ans = min(ans, dp[1][u][i] + dp[0][v][j] - c[u] + d[u]); // des so no v com o u antes
                    ans = min(ans, dp[0][u][i-1] + dp[0][v][j] + d[u]); // des so no v sem o u antes
                    
                    temp1[i+j] = ans;
                }   
            }
            forn(i,0,szu+szv) dp[2][u][i] = temp2[i];

            szu += szv;
        }

        return szu;
    };

    debug(1);
    dfs(0,-1);
    trace(
        forn(i,0,n) cout << dp[0][0][i] << " ";; cout << ln;
        forn(i,0,n) cout << dp[1][0][i] << " ";; cout << ln;
        forn(i,0,n) cout << dp[2][0][i] << " ";; cout << ln;
    );
    return 0;
}