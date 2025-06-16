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
    ll n, k; cin >> n >> k;
    string s; cin >> s;

    ll cnt0 = 0;
    ll cnt1 = 0;

    forn(i,0,n){
        if(s[i] == '0') cnt0++;
        else cnt1++;
    }

    ll z;

    z = (n-2*k)/2;

    if((cnt0 - z)%2 == 1 || (cnt0 - z) < 0){
        cout << "NO" << ln;
        return;
    }
    if((cnt1 - z)%2 == 1 || (cnt1 - z) < 0){
        cout << "NO" << ln;
        return;
    }

    cout << "YES" << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}