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

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout << setw(3) << x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

// const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll INF = 999ll;

void rec(ll i, ll j,ll l, vector<vector<v64>>& dp){
    if(l == -1) return;
    cout << "S";
    // debug(l);
    // debug(i);
    // debug(j);
    ll prox = dp[l][i][j];
    if(prox == j){
        cout << "C";
        rec(i+1, j+1, l-1, dp);
    }else if(prox == j+l){
        rec(i+1,j,l-1, dp);
        cout << "C";
    }else{
        // if(dp[idx-j-1][i+1][j] != -1 && dp[l+j-idx-1][idxi+1][idx+1] != -1){

        rec(i+1,j, prox-j-1, dp);
        cout << "C";
        rec(prox-j+i+1, prox+1, l+j-prox-1, dp);
    }
}

int main(){
    _;
    ll n;
    cin >> n;
    v64 a(n);
    v64 b(n);

    forn(i,0,n) cin >> a[i];
    forn(i,0,n) cin >> b[i];
    
    vector<vector<v64>> dp(n, vector<v64>(n+1, vector(v64(n+1, -1))));
       
    forn(j,0,n) dp[0][n][j] = INF;
    forn(i,0,n) dp[0][i][n] = INF;
    
    forn(i,0,n){
        forn(j,0,n){
            dp[0][i][j] = (a[i] == b[j] ? j : -1); 
        }
    }

    forn(l,1,n){
        forn(i,0,n-l){
            forn(j,0,n-l){
                //dp[l][i][j]
                // idx = j
                if(b[j] == a[i] && dp[l-1][i+1][j+1] != -1){
                    dp[l][i][j] = j;
                }
                for(ll idx = j+1; idx < j+l; idx++) if(b[idx] == a[i]){
                    ll idxi = idx-j+i;
                    if(dp[idx-j-1][i+1][j] != -1 && dp[l+j-idx-1][idxi+1][idx+1] != -1){
                        dp[l][i][j] = idx;
                        break;
                    }
                }
                // idx = j+l
                if(b[j+l] == a[i] && dp[l-1][i+1][j] != -1){
                    dp[l][i][j] = j+l;
                }
            }
        }
    }
 
    // forn(l,0,n){
    //     debug(l);
    //     forn(i,0,n){
    //         debugv(dp[l][i]);
    //     }
    // }    

    if(dp[n-1][0][0] == -1){
        cout << "NO" << ln;
    }else{
        cout << "YES\n";
        rec(0,0,n-1, dp);
        cout << ln;
    }
    return 0;
}