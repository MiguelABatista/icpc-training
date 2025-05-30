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
    const ll MOD = 1000000007;
    _;
    ll n = 0 ; 
    cin >> n ;
    ll x = 0 ; ll y = 0 ; 
    v64 L;
    cin >> x >> y ; 
    L.resize(n+1,0);
    L[1]=x;
    L[2] = y;

    if(n%2==0){cout << "Lleumas" << ln ;}
    else{cout << "Samuell" << ln;}
 

    return 0;
}