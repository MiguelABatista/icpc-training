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
    ll n; string s;
    cin >> n >> s;
    ll baixo = 0;
    ll alto = 0;
    forn(i,0,n){
        if(s[i] == '-') alto++;
        if(s[i] == '_') baixo++;
    }

    ll a,b;
    if(alto%2 == 0){
        a = alto/2;
        b = alto/2;
    }else{
        a = alto/2;
        b = alto/2 + 1;
    }
    
    cout << a*b*baixo << ln;
}
int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}