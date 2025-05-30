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
    ll n, m, k;

    cin >> n >> m >> k;
    v64 desired(n);
    v64 apartment(m);

    forn(i,0,n) cin >> desired[i];
    forn(i,0,m) cin >> apartment[i];

    sort(desired.begin(), desired.end());
    sort(apartment.begin(), apartment.end());

    ll d = 0;
    ll a = 0;
    ll resp = 0;
    while(d < n && a < m){
        if(abs(desired[d] - apartment[a]) <= k){
            a++;
            d++;
            resp++;
            continue;
        }
        if(desired[d] < apartment[a] - k){
            d++;
            continue;
        }
        if(apartment[a] < desired[d] - k){
            a++;
            continue;
        }
    }

    cout << resp << ln;
    return 0;
}