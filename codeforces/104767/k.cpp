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

ll calc(v64 v){
    ll n = v.size();
    ll resp = 0;
    forn(i,0,n-1){
        resp += gcd(v[i],v[i+1]);
    }
    return resp;
}

int main(){
    _;
    v64 v1 = { 2, 3, 9, 18, 6, 12, 4, 20, 10, 5, 15 };
    v64 v2 = { 2, 3, 9, 18, 6, 12, 4, 8, 16, 20, 10, 5, 15 };
    v64 v3 = { 1, 11, 13, 17, 19, 7, 14, 2, 3, 9, 18, 6, 12, 4, 8, 16, 20, 10, 5, 15 };

    cout << calc(v1) << ln;
    cout << calc(v2) << ln;
    cout << calc(v3) << ln;
    return 0;
}