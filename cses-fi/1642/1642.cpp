#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;
 
#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"
 
#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif
 
#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)
 
const ll INF = 0x3f3f3f3f3f3f3f3fll;
 
int main() {
    _;
    ll n, x; cin >> n >> x;
    v64 vec(n);

    forn(i,0,n){
        cin >> vec[i];
    }
    set<pair<ll, p64>> s;

    forn(i,0,n){
        forn(j,i+1,n){
            ll t = x - vec[i] - vec[j];
            auto it = s.lower_bound({t, {-INF, -INF}});
            if(it == s.end()) continue;
            if(it->first == t){
                cout << i + 1 << " " << j + 1 << " " << it->second.first + 1 << " " << it->second.second + 1 << ln;
                return 0;
            }
        }
        forn(j,0,i) s.insert({vec[j] + vec[i], {j,i}});
    }

    cout << "IMPOSSIBLE" << ln;
    return 0;
}
