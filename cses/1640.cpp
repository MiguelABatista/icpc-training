#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _;
    ll n; cin >> n;
    ll x; cin >> x;

    set<pair<ll,ll>> s;

    forn(i,0,n){
        ll aux; cin >> aux;
        s.insert({aux,i+1});
    }

    for(auto p: s){
        auto it = s.lower_bound({x-p.first, 0}); 
        if(it->second == p.second) it++;

        if(it != s.end() && it->first == x-p.first){
            cout << p.second << " " << it->second << ln;
            return 0; 
        }
    }
    cout << "IMPOSSIBLE" << ln;
    return 0;
}