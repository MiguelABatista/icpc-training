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

ll funfa(ll bound, v64 &vec, v64 &colors){
    // 0 for blue
    // 1 for red
    ll n = vec.size();
    ll cor = -1;
    ll counter = 0;
    forn(i,0,n){
        if(vec[i] <= bound) continue;

        if(cor == -1){
            cor = colors[i];
            if(cor == 0) counter++;
            continue;
        }

        if(cor == colors[i]) continue;

        cor = colors[i];
        if(cor == 0) counter++;
    }
    
    return counter;
}

void solve(){
    ll n; ll k;
    cin >> n >> k;
    v64 colors(n);
    v64 vec(n);
    
    forn(i,0,n){
        char c; cin >> c;
        if(c == 'B'){
            colors[i] = 0;
        }else{
            colors[i] = 1;
        }
    }

    forn(i,0,n) cin >> vec[i];

    ll left = 0; ll right = 1'000'000'001; 
    
    ll ans;
    while(left < right){
        debug(left);
        debug(right);
        ll mid = (left + right)/2;
        if(funfa(mid, vec, colors) <= k){
            right = mid;
            ans = mid;
        }else{
            left = mid+1;
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