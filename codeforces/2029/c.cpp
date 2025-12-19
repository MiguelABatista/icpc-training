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

bool testa(ll target, v64& vec, v64& maxrat){
    ll n = vec.size();
    v64 dp(n+1);
    dp[n] = target;
    
    if(maxrat[n-2] >= target) return true;

    for(ll i = n-1; i>= 0; i--){
        ll x = dp[i+1];
        if(vec[i] >= x) dp[i] = x-1;
        else dp[i] = x+1;
    }

    debugv(dp);
    forn(i,2,n){
        if(dp[i] <= maxrat[i-2]) return true;
    }
    if(dp[1] <= 0) return true;
    return false;
}

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];
    if(n == 1){
        cout << 0 << ln;
        return;
    }
    v64 rat(n), maxrat(n);
    rat[0] = 1;
    maxrat[0] = 1;

    forn(i,1,n){
        rat[i] = rat[i-1];
        if(rat[i] > vec[i]) rat[i]--;
        if(rat[i] < vec[i]) rat[i]++;
        maxrat[i] = max(maxrat[i-1], rat[i]);
    }
    debugv(rat);
    debugv(maxrat);

    ll ans = 0;
    ll l = 0;
    ll r = n;
    while(l <= r){
        ll mid = (l+r)/2;   
        debug(mid);
        if(testa(mid, vec, maxrat)){
            debug("true");
            ans = mid; 
            l = mid+1;
        }else{
            debug("false");
            r = mid-1;
        }
    }
    cout << ans << ln;
    trace(cout << "----------\n\n";);
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}