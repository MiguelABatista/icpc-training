#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
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
const ll ep = 0.00000001;

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    vector<ld> lv(n);
    forn(i,0,n) lv[i] = log(vec[i]);
    vector<pair<ld, ll>> dp(n);

    dp[0] = {lv[0], 1};

    forn(i,1,n){
        if(dp[i-1].first <= log(dp[i-1].second+ep)){ // dp[i-1].first <= dp[i-1].second+1
            dp[i] = {lv[i], 1}; 
        }else{ 
            dp[i] = {dp[i-1].first + lv[i] - log(dp[i-1].second+1), dp[i-1].second+1};
            while(dp[i].second > 1){
                if(vec[i-dp[i].second+1] == dp[i].second) dp[i].second--;
                else break;
            }
        }
    }

    forn(i,0,n){
        ll resp = dp[i].second;
        while (i - resp >= 0 && vec[i-resp] == resp+1){
            resp++; 
        }
        cout << resp << " ";
    }

    cout << ln;
    trace(
    forn(i,0,n){
        cout << dp[i].first << " : " << dp[i].second << ln; 
    }
    cout << "----------------\n\n"; 
    );
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}