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
    ll sum = ((n+1)*n)/2;

    if(sum % 2 == 1){
        cout << "NO" << ln;
        return 0;
    }

    cout << "YES" << ln;
    ll target = sum/2;

    set<ll> grupo_1;
    set<ll> grupo_2;
    ll curr_sum = 0;

    for(ll i = n; i > 0; i--){
        if(curr_sum + i <= target){
            curr_sum += i;
            grupo_1.insert(i);
        }else{
            grupo_2.insert(i);
        }
    }

    cout << grupo_1.size() << ln;
    for(ll x: grupo_1) cout << x << " ";
    cout << ln;
    
    cout << grupo_2.size() << ln;
    for(ll x: grupo_2) cout << x << " ";
    cout << ln;
    
    return 0;
}