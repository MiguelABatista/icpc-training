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

int main(){
    _;
    ll n; cin >> n;
    if(n == 1){
        cout << 1 << ln;
        return 0;
    }

    if(n < 4){
        cout << "NO SOLUTION" << ln;
        return 0;
    }
    
    ll i = 2;

    while(i <= n){
        cout << i << " ";
        i += 2;
    }
    i = 1;
    while(i <= n){
        cout << i << " ";
        i += 2;
    }
    cout << ln;
    return 0;
}