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

    ll lim = 1;
    forn(i,0,k) lim *= (n+1);

    ll resp = 0;
    ll respsum = 0;
    forn(i,0,lim){
        ll aux = i;
        ll x = 0;
        ll sum = 0;
        forn(j,0,k){
            ll curr = aux%(n+1);
            sum += curr;
            x ^= curr;
            aux /= n+1;
        }
        if(x == n && sum >= respsum){
            resp = i;
            respsum = sum;
        }
    }
    cout << respsum << ln;
    cout << resp << ln;
    ll aux = resp;
    forn(i,0,k){
        ll curr = aux%(n+1);
        aux /= n+1;
        cout << curr << " ";
    }
    cout << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}