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

void solve(){
    ll n; cin >> n;
    v64 freq(2*n);

    forn(i,0,2*n){
        ll x; cin >> x;
        x--;
        freq[x]++;
    }
    
    ll amt = 0;
    ll imp = 0;
    ll sob = 0;
    ll resp = 0;

    for(ll f: freq) if(f != 0){
        if(f%2 == 0){
            resp += 2;
            amt++;
            sob += (f-2)/2;
        }else{
            resp += 1; 
            imp++;
            sob += (f-1)/2;
        }
    }

    debug(amt);
    debug(imp);
    debug(sob);
    debug(resp);
    if((n-amt)%2 == 1 && sob != 0){
        if(imp == 1) resp -= 1;
        if(imp == 0) resp -= 2;
    }

    cout << resp << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}