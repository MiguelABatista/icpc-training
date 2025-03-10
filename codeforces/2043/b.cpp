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
    ll n, d;
    cin >> n >> d;
    v64 resp;
    resp.push_back(1);

    if(d%3 == 0 || n >= 3){
        resp.push_back(3);
    }
    
    if(d%5 == 0){
        resp.push_back(5);
    }

    if(d%7 == 0 || n >= 3){
        resp.push_back(7);
    }

    if(d%9 == 0 || (d%3 == 0 && n >= 3) || n >= 6){
        resp.push_back(9);
    }  

    for(auto x: resp){
        cout << x << ' ';
    }
    cout << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();

    return 0;
}