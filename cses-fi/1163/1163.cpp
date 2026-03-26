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
    ll x, n; cin >> x >> n;
    multiset<ll> len;
    len.insert(x);
    set<ll> pos;
    pos.insert(0);
    pos.insert(x);

    forn(i,0,n){
        ll p; cin >> p;
        ll nxt = *pos.lower_bound(p);
        ll pre = *prev(pos.lower_bound(p));
        len.erase(len.find(nxt-pre));
        len.insert(nxt - p);
        len.insert(p - pre);
        pos.insert(p);
        debugv(len); 
        debugv(pos);
        cout << *prev(len.end()) << " ";
    } 
    cout << ln;
    return 0;
}
