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
const ll MOD = 1'000'000'007;

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];
    ll qnt_imp = 0;
    ll qnt_par = 1;

    forn(i,0,n){
        ll aux = __builtin_popcountll(vec[i]);
        if(aux%2 == 0){
            qnt_imp = (qnt_imp*2)%MOD;
            qnt_par = (qnt_par*2)%MOD;
        }else{
            ll nxt = (qnt_imp+qnt_par)%MOD; 
            qnt_imp = nxt;
            qnt_par = nxt;
        }
    }
    cout << qnt_imp << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}