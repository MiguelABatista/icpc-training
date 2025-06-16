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

ll menor_div(ll y){
    for(ll i = 2; i*i <= y; i++){
        if(y%i == 0) return i;
    }
    return y;
}

int main(){
    _;
    ll y, k; cin >> y >> k;
    ll x = 1;
    
    while(k > 0){
        ll div = menor_div(y);
        y /= div;
        ll passo = min(k,div);
        x *= passo;
        k -= passo;
    }
    
    cout << x << ln;
    return 0;
}