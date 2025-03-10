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
    ll n, t; cin >> n >> t;
    map<char, v64> mp;
    forn(i, 0, n) {
        char c; cin >> c;
        ll v; cin >> v;
        mp[c].push_back(v);
    }

    ll ans = 0;
    for (auto& [k, vec] : mp) {
        sort(vec.begin(), vec.end());
        ll curr = 0;
        for(auto x: vec) {
            curr += x;
            if (curr > t) break;
            ans++;
        }
    }
    cout << ans << ln;

    return 0;
}