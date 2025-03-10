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

// 2**30 = 1'073'741'824

void solve(){
    ll n; ll x;
    cin >> n >> x;

    if(n == 1){
        cout << x << ln;
        return;
    }

    ll curr_or = 0;
    ll idx = 0; 
     
    forn(i,0,n){
        curr_or = curr_or | i;
        if(((~x) & curr_or) > 0){
            break;
        }
        idx = i;
    }
    
    ll all_or = 0;
    
    forn(i,0,idx+1) all_or = all_or | i;

    if( all_or == x){
        forn(i,0,idx+1) cout << i << ' ';
        forn(i, idx+1, n) cout << x << ' ';
        cout << ln;
        return;
    }

    if(idx == n-1){
        idx--;
    }

    forn(i,0,idx+1) cout << i << ' ';
    forn(i, idx+1, n) cout << x << ' ';
    cout << ln;
    return;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}