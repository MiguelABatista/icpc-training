#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll exp(ll b, ll e){
    ll ans = 1;
    forn(i,0,e) ans *= b;
    return ans;
}

ll count(ll b, ll n){
    ll ans = 0;
    while(n >= 1){
        if(n%b == 0) ans++;
        n /= b;
    }
    return ans;
}

int main(){
    _;

    forn(n,1'000'000,10'000'000){
        ll ans = 1;
        forn(b,2,n+1){
            ans = max(ans,count(b,n));
            if(exp(b,ans) > n) break;
        }
        
        if(ans == 1) cout << n << ln;
    }

    return 0;
}