#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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
    ll n, m; cin >> n >> m;
    multiset<ll> s;
    forn(i,0,n){
        ll x; cin >> x;
        s.insert(x);
    }
    forn(i,0,m){
        ll x; cin >> x;
        auto iit = s.upper_bound(x);
        if(iit == s.begin()){
            cout << -1 << ln;
            continue;
        }
        auto it = prev(iit);
        cout << (*it) << ln;
        s.erase(it);
    }
    return 0;
}
