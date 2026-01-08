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

void solve_pequeno(ll n, ll k, v64& vec){  
    v64 dp(k);
    ll resp = 0;
    forn(i,0,n){
        dp[0]++;
        
        if(vec[i] == 1){
            ll aux = dp[k-1];
            forn(j,1,k){
                dp[j] = dp[j-1];
            }
            dp[0] = aux;
        }

        resp += dp[0];
    }   
}

void solve_grande(ll n, ll k, v64& vec){

}

void solve(){
    ll n, k; cin >> n >> k;
    v64 vec(n);
    
    forn(i,0,n){
        cin >> vec[i];
        vec[i] = (vec[i]%k == 0 ? 1 : 0);
    }

    if(k > n){
        k = n+1;
    }

    v64 dp(k);
    ll shift = 0;
    ll resp = 0;
    forn(i,0,n){
        debugv(dp);
        dp[shift]++;
        if(vec[i] == 1) shift++;
        shift %= k;
        resp += dp[shift];
    }
    debugv(dp);
    cout << resp << ln;
}

int main(){
    _;
    ll t = 1;
    while(t--) solve();
    return 0;
}