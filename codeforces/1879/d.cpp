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
const ll MAXA = 1'000'000'001;
// const ll MAXA = 10;
const ll MOD = 998244353;

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    v64 bits(n);
    ll resp = 0;
    for(ll pot2 = 1; pot2 < MAXA; pot2 <<= 1){
        forn(i,0,n) bits[i] = !!(vec[i]&pot2); 
        debugv(bits);
        ll curr_resp = 0;
        ll val = 0;
        ll amt = 0;
        val = bits[0];
        amt = bits[0];
        curr_resp += val;
        forn(i,1,n){
            debug(amt);   
            debug(val);   
            ll newval = 0;
            ll newamt = 0;
            if(bits[i] == 0){
                newval = val + amt;
                newamt = amt;
            }else{
                ll tot = ((i+1)*(i))/2;
                newval = tot-val + (i - amt + 1);
                newamt = (i - amt + 1);
            }

            val = newval;
            amt = newamt;
            curr_resp = (curr_resp + val)%MOD;
        }
        debug(amt);   
        debug(val);   
        debug(curr_resp);
        resp = (resp + (curr_resp*pot2)%MOD)%MOD;
    }
    cout << resp << ln;

}

int main(){
    _;
    ll t =1;
    while(t--) solve();
    return 0;
}