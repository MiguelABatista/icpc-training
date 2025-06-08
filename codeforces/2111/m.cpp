#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;
typedef long double ld;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;
ll k, n;

p64 solve(vector<ld> &vec){
    vector<ld> dp(n,-INF);
    vector<ll> left(n,0-1);
    
    ld sw = 0;
    forn(i,0,k) sw += vec[k];
    
    dp[k-1] = sw;
    left[k-1] = 0;
    
    ll best_dp = k-1;
    forn(i,k, n){
        sw += (vec[i] - vec[i-k]);

        if(sw > dp[i-1]+vec[i]){
            left[i] = i-k;
            dp[i] = sw;
        }else{
            left[i] = left[i-1];
            dp[i] = dp[i-1]+vec[i];
        }
        if(dp[best_dp] < dp[i]) best_dp = i;
    }
    if(best_dp < 0) return {-1,-1};
    
    return {left[best_dp], best_dp};
}

int main(){
    _;
    cin >> n;
    cin >> k;

    v64 vec(n);
    
    forn(i,0,n) cin >> vec[i];

    ld l = 0;
    ld r = 1'000'000'000;
    ld mid = r + (r-l)/2;

    p64 p;

    vector<ld> aux(n);
    forn(nada,0,50){
        forn(i,0,n) aux[i] = vec[i] - mid;

        p = solve(aux);

        if(p.first == -1){
            r = mid;
        }else{
            l = mid;
        }
        mid = r + (r-l)/2;
    }

    cout << p.first+1 << " " << p.second+1 << ln;
    return 0;
}