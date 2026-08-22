#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;




/* ll bsearch (ll L , ll R  , ll cvalue , ll multi) {
    ll l  = L ;
    ll r = R ; 
    ll mid  = (r+l)/2;

    ll bestmid = mid;
    while (l<r) {
        if (c(mid,multi) < cvalue) {

            l = mid+1 ;
            mid = (l+r)/2;
            bestmid = mid;
        }
        else {
            r = mid-1 ; 
            mid = (l+r)/2;

            if (c(mid,multi) >= cvalue)
                bestmid=mid;
        }

    }
    return bestmid;


} */


int main() {
    _;
    ll n ;
    cin >> n ; 

    vll fib = {1,2};

    while (fib[fib.size()-1]<1e9) {
        fib.push_back(fib[fib.size()-1]+fib[fib.size()-2]);
    }
   // cout << fib.size() << ln;

    vll ans (n);

    forn(i,0,n) {
        ll a ,  b; 
        cin >> a >> b ;
        forn (j,0,fib.size()) {
            if (fib[j]*a>=b) {
                ans[i]=j;
                break;
            }
        }
        
    }
    forn(i,0,n)
        cout << ans[i]+1<< ln;

    return 0;
}
