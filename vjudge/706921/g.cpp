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
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif
 
int main(){
    _;
    ll n; cin >> n; 
    v64 vec(n);
    ll cum_sum = 0;
 
    forn(i,0,n){
        cin >> vec[i];
        cum_sum += vec[i];
    }
 
    if(cum_sum%2 == 1){
        cout << -1 << ln;
        return 0;
    }
 
    ll target = cum_sum/2;
 
    vector<bitset<102>> dp(target+1);
 
    forn(i,0,n){
        for(ll t = target;t >= 0; t--){
            if(t - vec[i] < 0){
               continue;
            }
            if(dp[t].any()){
                continue;
            }            
            if(t == vec[i]){
                dp[t][i] = true;
                continue;
            }
            if(dp[t-vec[i]].any()){
                dp[t] |= dp[t-vec[i]];
                dp[t][i] = true; 
            }
        }
    }
    if(!(dp[target].any())){
        cout << -1 << ln;
        return 0;
    }
 
    ll sum_a = 0;
    ll sum_b = 0;
    ll idxa = 0;
    ll idxb = 0;
    ll counter = 0;
    while(counter < n){
        if(sum_b < sum_a){
            if(!dp[target][idxb]){
                cout << vec[idxb] << " ";
                sum_b += vec[idxb];
                counter++;
            } 
            idxb++;
        }else{
            if(dp[target][idxa]){
                cout << vec[idxa] << " ";
                sum_a += vec[idxa];
                counter++;
            } 
            idxa++;
        }
    }
    cout << ln;
    return 0;
}