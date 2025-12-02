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

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    v64 acc(n);

    forn(i,0,n) {
        cin >> vec[i];
        acc[i] = vec[i] + (i == 0 ? 0 : acc[i-1]);
    }

    vector<v64> dp(n,v64(n, INF));

    forn(i,0,n) dp[i][i] = 0;

    function<ll (ll, ll)> sum = [&](ll a, ll b){
        return (acc[b]-(a == 0 ? 0 : acc[a-1]));
    };

    forn(t,0,n){
        forn(i,0,n-t){
            ll j = i+t;
            forn(x,i,j){
                dp[i][j] = min(dp[i][j], dp[i][x] + dp[x+1][j] + sum(i,x)+sum(x+1,j));
            }
        }
    }
    cout << dp[0][n-1] << ln;
}

int main(){
    _;
    solve();    
    return 0;
}