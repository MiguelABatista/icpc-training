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
    ll n, x; cin >> n >> x;

    v64 vec(n);
    
    forn(i,0,n) cin >> vec[i];

    ll p1 = 0;
    ll p2 = 0;
    ll sum = vec[0];
    ll count = 0;
    if(sum == x) count++;
    
    while(p2 < n-1){    
        if(sum + vec[p2+1] <= x){
            sum += vec[p2+1];
            p2++;
        }else{
            sum -= vec[p1];
            p1++;
        } 

        if(sum == x) count++;
    }

    cout << count << ln;
    return 0;
}