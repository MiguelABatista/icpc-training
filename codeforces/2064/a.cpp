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
    ll n; cin >> n;
    string s; cin >> s;
    s.push_back('0');

    ll count = 0;

    for(ll i = n-1; i >= 0; i--){
        if(s[i] == '1' && s[i+1] == '0') count += 2;
    }

    if(s[n-1] == '1'){
        count--;
    }
    
    cout << count << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}