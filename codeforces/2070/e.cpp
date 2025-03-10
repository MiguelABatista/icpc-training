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
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n){
        char c; cin >> c;
        vec[i] = c-'0';
    }
    v64 cum_sum(n,0);
    cum_sum[0] =vec[0];
    
    forn(i,1,n){
        cum_sum[i] = cum_sum[i-1] + vec[i];
    }

    ll resp = 0;
    set<p64> s; // tam, #1
    
    forn(i,0,n){

    }
}

int main(){
    _;
    ll t = 1; 
    while(t--) solve();
    return 0;
}