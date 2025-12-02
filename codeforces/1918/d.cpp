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

bool testa(ll bound, ll n, v64& vec){
    v64 dp(n);

    multiset<ll> s;
    s.insert(0);
    ll p1 = -1;
    ll p2 = 0;

    dp[0] = vec[0];
    s.insert(dp[0]);
    p2++;
    ll curr_sum = vec[0];

    while (p2 < n){
        debug(p1);
        debug(p2);
        debug(curr_sum);
        debugv(s);
        if(curr_sum > bound){
            curr_sum -= vec[p1+1];
            
            s.erase(s.find(p1 == -1? 0 : dp[p1]));
            p1++;
        }else{
            dp[p2] = *s.begin() + vec[p2];
            curr_sum += vec[p2];
            s.insert(dp[p2]);
            p2++;
        }
    }

    debug(bound);
    debugv(dp);
    
    curr_sum = 0;
    ll ans = INF;
    for(ll i = n-1; i >= 0; i--){
        curr_sum += vec[i];
        ans = min(ans, dp[i]);
        if(curr_sum > bound) break;
    }

    debug(ans);
    return ans <= bound;
}

void solve(){
    ll n; cin >> n;
    v64 vec(n);

    forn(i,0,n) cin >> vec[i];
    
    ll ans = INF;
    ll l = 0;
    ll r = 100'000'000'000'000ll;
    // ll r = 10;
    while(l <= r){
        trace(cout << ln;);
        ll mid = (l+r)/2;
        
        if(testa(mid, n, vec)){
            ans = mid;
            r = mid-1;
        }else{
            l = mid+1;
        }
    }
    cout << ans << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}