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
    
    forn(i,0,n) cin >> vec[i];

    set<ll> s;

    ll p1 = 0;
    ll p2 = 0;
    ll resp = 0;
    while(p2 < n){    
        if(s.find(vec[p2]) == s.end()){
            s.insert(vec[p2]);
            resp = max(resp, p2-p1+1);
            p2++;
        }else{
            s.erase(vec[p1]);
            p1++;
        }
    }

    cout << resp << ln;
    return 0;
}