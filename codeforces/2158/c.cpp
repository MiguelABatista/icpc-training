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
    ll n, k; cin >> n >> k;
    v64 a(n), b(n);
    forn(i,0,n) cin >> a[i];
    forn(i,0,n) cin >> b[i];

    k = k%2;
    forn(i,0,n) b[i] *= k;

    v64 dp0(n), dp1(n);

    dp0[0] = a[0];
    dp1[0] = a[0] + b[0];

    forn(i,1,n){
        dp0[i] = max(a[i], dp0[i-1]+ a[i]);
        dp1[i] = max(max(a[i]+b[i], dp0[i-1]+a[i]+b[i]), dp1[i-1] + a[i]);
    }

    ll resp = -INF;
    forn(i,0,n) resp = max(resp, dp1[i]);
    cout << resp << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}