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
    ll x; cin >> x;
    multiset<ll> ener;
    ener.insert(0);
    ener.insert(0);
    ener.insert(0);

    ll cnt = 0;
    while(true){
        auto it = ener.begin();
        if(*it == x) break;
        ener.erase(it);
        ll lb = *ener.begin();
        ll next = 2*lb+1; 
        if(next > x) next = x;
        ener.insert(next);
        cnt++;
    }

    cout << cnt << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}