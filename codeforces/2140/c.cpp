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
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    ll best_par = 2*vec[0];
    ll best_imp = -1;
    ll best_delta = -INF;

    forn(i,1,n){
        ll curr_delta = -1;
        if((i&1) == 0){
            curr_delta = -2*vec[i] + i + best_imp;
            best_par = min(best_par, 2*vec[i]+i);
        }else{
            curr_delta = 2*vec[i] + i - best_par;
            best_imp = max(best_imp, 2*vec[i]-i);
        }
        
        best_delta = max(best_delta, curr_delta);
        debug(i);
        debug(best_par);
        debug(best_imp);
        debug(best_delta);
    }

    best_delta = max(best_delta, n-1 - (n-1)%2);
    ll tot = 0;
    forn(i,0,n) tot += (1 - 2*(i&1))*vec[i];
    debug(tot);
    debug(best_delta);
    cout << tot+best_delta << ln;
    trace(cout << "-------------\n\n");
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}