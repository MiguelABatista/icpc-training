#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n; cin >> n;
    v64 a(n), b(n);

    forn(i,0,n) cin >> a[i];
    forn(i,0,n) cin >> b[i];

    set<ll> s;

    ll la;
    ll lb;

    la = a[n-1];
    lb = b[n-1];
    if(la == lb){
        cout << n << ln;
        return;
    }

    ll found = false;
    for(ll i = n-2; i >= 0; i--){
        if(a[i] == b[i]) found = true;
        if(s.count(a[i])) found = true;
        if(s.count(b[i])) found = true;

        if(a[i] == la || b[i] == lb) found = true;
        s.insert(la);
        s.insert(lb);
        la = a[i];
        lb = b[i];
        if(found){
            debug(i);
            cout << i+1 << ln;
            return;
        }
    }
    cout << 0 << ln;
}
int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}