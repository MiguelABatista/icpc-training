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


int main(){
    _;
    ll n, h; cin >> n >> h;
    
    v64 hs(n);
    
    forn(i,0,n) cin >> hs[i];

    ll curr = 0;
    forn(i,0,n){
        ll space = (h-curr) - hs[i];
        if(space < 0){
            cout << "impossible" << ln;
            return 0;
        }
        if(space%2 == 0){
            curr--;
            curr = max(curr, 0ll);
        }else{
            curr++;
        }
    }
    
    if(curr != 0){
        cout << "impossible" << ln;
        return 0;
    }
    cout << "possible" << ln;
    return 0;
}