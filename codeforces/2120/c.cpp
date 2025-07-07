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
    ll n, m; cin >> n >> m;
    
    if(m < n || m > (n*(n+1))/2 ){
        cout << -1 << ln;
        return;
    }
    set<ll> not_used;
    
    forn(i,2,n+1) not_used.insert(i);

    v64 path;
    ll sum = n;
    for(ll i = n; i > 1; i--){
        if(sum + i - 1 <= m){
            sum += i -1;
            path.push_back(i);
            not_used.erase(i);
        }
    }
    path.push_back(1);
    for(ll x : not_used) path.push_back(x);

    cout << path[0] << ln;
    forn(i,0,n-1){
        cout << path[i] << " " << path[i+1] << ln;
    }
    // forn(i,0,n) cout << path[i] << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}