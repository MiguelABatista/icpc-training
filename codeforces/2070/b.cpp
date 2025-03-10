#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n, x, k;
    cin >> n >> x >> k;
    v64 vec(n);
    forn(i,0,n){
        char c;
        cin >> c;
        if(c == 'L'){
            vec[i] = -1;
        }else{
            vec[i] = 1;
        }
    }

    v64 cum_sum(n,0);
    cum_sum[0] = vec[0];

    ll first_zero = -1;
    ll back_to_zero = -1;

    if(cum_sum[0] == -x && first_zero == -1){
        first_zero = 0;
    }
    if(cum_sum[0] == 0 && back_to_zero == -1){
        back_to_zero = 0;
    }

    forn(i,1,n){
        cum_sum[i] = cum_sum[i-1] + vec[i];
        if(cum_sum[i] == -x && first_zero == -1){
            first_zero = i;
        }
        if(cum_sum[i] == 0 && back_to_zero == -1){
            back_to_zero = i;
        }
    }

    debug(k);
    debug(first_zero);
    debug(back_to_zero);

    if(first_zero > k || first_zero == -1){
        cout << 0 << ln;
        
        return;
    }

    ll spare_time = k - (first_zero+1);
    debug(spare_time);

    if(back_to_zero == -1){
        cout << 1 << ln;
        return; 
    }
    
    cout << spare_time/(back_to_zero+1) + 1 << ln;
    return;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}