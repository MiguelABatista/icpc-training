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
#define debugp(v) trace({cout << #v": "; for (auto y : v) cout<< y.first << ":" << y.second << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n, q; cin >> n >> q;
    v64 x(n);
    forn(i,0,n) cin >> x[i];
    map<ll,ll> resp;

    resp[n-1] += 1;
    forn(i,1,n){
        ll amt = x[i]-x[i-1]-1;
        resp[i*(n-i)] += amt;
        resp[(i+1)*(n-i)-1] += 1;
    }
    while(q--){
        ll k; cin >> k;
        cout << resp[k] << " ";
    }
    debugp(resp);
    cout << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}