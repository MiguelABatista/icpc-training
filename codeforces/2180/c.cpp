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
const ll LOG = 31;

void solve(){
    ll n, k; cin >> n >> k;

    if(k%2 == 1){
        forn(i,0,k) cout << n << " ";; cout << ln;
        return;
    } 

    v64 vec(k);
    ll livres = k-1;
    bool first = false;
    for(ll i = LOG; i>=0; i--){
        ll pot2 = 1ll<<i;
        
        if(n&pot2){
            if(!first) first = true;
            forn(j,0,k) vec[j] += pot2;
            if(livres != -1){
                vec[livres] -= pot2;
                livres--;
            } else{
                vec[0] -= pot2; 
            }
        }else{
            if(!first) continue;
            for(ll j = k-1; j > livres+((k-1 - livres)%2); j--){
                debug(j);
                vec[j] += pot2; 
            }
        }
        debugv(vec);
        debug(livres); 
    }
    ll sum = 0;
    ll x = 0;
    forn(i,0,k){
        sum += vec[i];
        x ^= vec[i];
        cout << vec[i] << " ";
    }
    cout << ln;
    // cout << sum << ln;
    debug(sum);
    debug(x); 
}  

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}