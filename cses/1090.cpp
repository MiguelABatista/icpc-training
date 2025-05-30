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

int main(){ _;
    ll n, x;
    cin >> n >> x;
    
    v64 pesos(n);
    
    forn(i,0,n) cin >> pesos[i];

    sort(pesos.begin(), pesos.end());

    ll p1 = 0;
    ll p2 = n-1;
    ll resp = 0;
    while(p1 <= p2){
        if(p1 == p2){
            resp++;
            break;
        }
        if(pesos[p1]+pesos[p2] <= x){
            p1++;
            p2--;
            resp++;
        }
        else{
            p2--;
            resp++;
        }
    }

    cout << resp << ln;
    
    return 0;
}