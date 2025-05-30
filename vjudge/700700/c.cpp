#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

v64 a,b;
ll n, k;

bool testa(ll t){
    ll k_ = k;

    forn(i,0,n){
        k_ += min(b[i] - t * a[i], 0ll);
        if(k_ < 0) return false;
    }

    debug(k_);
    
    return true;
}

int main(){
    _;
    cin >> n >> k;
    a.resize(n);
    b.resize(n);

    forn(i,0,n) cin >> a[i];
    forn(i,0,n) cin >> b[i];

    ll l = 0;
    ll r = 2'000'000'000;
    ll ans = 0;

    while(l <= r){
        ll mid = (l+r)/2;
        // cout << l << " " << mid << " " << r << ln;

        if(testa(mid)){
            ans = mid;
            l = mid+1;
        }else r = mid-1;
    }

    cout << ans << ln;
    return 0;   
}