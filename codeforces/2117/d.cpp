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

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    v64 diff(n-1);
    forn(i,0,n-1){
        diff[i] = vec[i+1] - vec[i];
    }
    
    forn(i,0,n-1){
        if(diff[i] != diff[0]){
            cout << "NO" << ln;
            return;
        }
    }

    ll d = diff[0];

    if(d < 0){
        forn(i,0,n){
            vec[i] += d*(n-i);
        }
    }
    if(d > 0){
        forn(i,0,n){
            vec[i] -= d*(i+1);
        }
    }

    if(vec[0] < 0 || vec[0] % (n+1) != 0 ) {
        cout << "NO" << ln;
        return;
    }

    ll aux = vec[0]/(n+1);

 
    forn(i,0,n){
        vec[i] -= aux*(n+1);
    }
    

    forn(i,0,n){
        if(vec[i] != 0){
            cout << "NO" << ln;
            return;
        }
    }

    cout << "YES" << ln;
}
int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}