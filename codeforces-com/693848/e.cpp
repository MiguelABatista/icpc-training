#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
const ll INF = 999;
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
const ll INF = 0x3f3f3f3f3f3f3f3fll;
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << setw(2) << xx << " "; cout << ln)



int main() {
    _;
    ll n, p, s; cin >> n >> p >> s;
    s++;

    vector<vector<vector<vll>>> dp(n+1, vector<vector<vll>>(3,vector<vll>(s, vll(n+1, INF))));
    vll t(3); cin >> t[0] >> t[1] >> t[2];
    vll d(3); cin >> d[0] >> d[1] >> d[2];
    
    // dp[i][x][k][j] = melhor tempo usando k pitstops com o pneu x na volta i e com j voltas sobrando no pneu
    // no final da volta i (indexado a 1)

    forn(x,0,3) dp[0][x][0][d[x]] = 0;
    vector<vll> best(s, vll(n+1,INF));
    best[0][0] = 0;

    forn(i,1,n+1){
        forn(x,0,3){
            forn(j,0,d[x]){
                forn(k,0,s){
                    dp[i][x][k][j] = dp[i-1][x][k][j+1] + t[x]; 
                    if(dp[i][x][k][j] > INF) dp[i][x][k][j] = INF;
                    best[k][i] = min(best[k][i], dp[i][x][k][j]);
                }
            }
        }    
        
        // para j = n-1 temos que usar pitstop
        forn(k,1,s){
            forn(x,0,3){
                dp[i][x][k][d[x]] = best[k-1][i] + p; 
                if(dp[i][x][k][d[x]] > INF) dp[i][x][k][d[x]] = INF;
                best[k][i] = min(best[k][i], dp[i][x][k][d[x]]);
            }
        }
    }

    ll resp = INF;
    forn(x,0,3){
        forn(j,0,d[x]+1){
            forn(k,0,s){
                trace(cout << x << " " << j << " " << k << " : "; forn(i,0,n+1) cout << setw(4) << dp[i][x][k][j] << " ";; cout << ln;)
                resp = min(resp, dp[n][x][k][j]); 
            }
        }
    }
    cout << resp << ln;
    return 0;
}
