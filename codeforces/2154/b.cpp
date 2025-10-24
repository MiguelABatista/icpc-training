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
    v64 a(n);
    forn(i,0,n) cin >> a[i];
    ll ans = 0;
    
    ll pref_max = -INF;    
    forn(i,0,n){
        pref_max = max(a[i], pref_max);
        if(i%2 == 1) a[i] = pref_max;
    }

    // debugv(a);
    forn(i,0,n){
        if(i%2 == 0){
            ll bound = INF;
            if(i > 0) bound = min(bound, a[i-1]);
            if(i < n-1) bound = min(bound, a[i+1]);
            if(a[i] >= bound){
                ans += a[i] - bound + 1;
                a[i] = bound-1;
            }
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