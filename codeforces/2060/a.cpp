#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll a1, a2, a4, a5;
    cin >> a1 >> a2 >> a4 >> a5;

    ll p1 = a1 + a2;
    ll p2 = a4 - a2;
    ll p3 = a5 - a4;

    if(p1 == p2){
        if(p1 != p3){
            cout << 2 << ln;
            return;
        }else{
            cout << 3 << ln;
            return;
        }
    }

    if(p2 == p3 || p1 == p3){
        cout << 2 << ln;
        return;
    }
    cout << 1 << ln;
    return;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}