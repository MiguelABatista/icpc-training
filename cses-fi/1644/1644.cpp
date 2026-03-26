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
    ll n; cin >> n;
    ll a, b; cin >> a >> b;
    v64 vec(n+1), acc(n+1);

    forn(i,1,n+1) cin >> vec[i];
    forn(i,1,n+1) acc[i] = vec[i] + acc[i-1];
    multiset<ll> ms;

    ll resp = -INF;
    for(ll i = n; i >= 0; i--){
        if(i+a <= n) ms.insert(acc[i+a]);
        if(i+b+1 <= n) ms.erase(ms.find(acc[i+b+1]));
        if(ms.empty()) continue;
        resp = max(resp, *prev(ms.end()) - acc[i]);
    }
    resp = max(resp, *prev(ms.end()));
    cout << resp << ln;
    return 0;
}
