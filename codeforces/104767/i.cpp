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
    ll n = 0 ; ll m = 0 ;  
    cin >> n ;
    cin >> m ; 
    vector<ll> v (n,0);
    forn(i,0,m){
        cin >> v[i] ;  
    }
    pair<ll,ll> p ; 
    forn(i,0,n){
        if (n%v[i]==0){
            p.first = min(v[i],n/v[i]);
            p.second = max(v[i],n/v[i]);
            break;
        }
    }

    cout << p.first << " " << p.second << ln ;  
    return 0;
}