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

int main(){
    _;
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n){
        cin >> vec[i];
        vec[i]--;
    }

    v64 inv(n);
    forn(i,0,n) inv[vec[i]] = i;
    
    ll cnt = 1;
    forn(i,0,n-1){
        if(inv[i] > inv[i+1]) cnt++;
    }

    // forn(i,0,n) cout << inv[i];; cout << ln;

    ll resp = 0;
    while(cnt > 1){
        cnt = (cnt+1)/2;
        resp++;
    }    
    cout << resp << ln;
    return 0;
}
