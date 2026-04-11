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
    vector<p64> vec(n);
    forn(i,0,n) cin >> vec[i].first;
    forn(i,0,n) vec[i].second = i;

    sort(vec.begin(), vec.end());

    forn(i,0,n){
        auto it = lower_bound(vec.begin() + i + 1, vec.end(), (p64){x - vec[i].first, -1});
        if(it == vec.end()) continue;
        if((*it).first != x - vec[i].first) continue;
        cout << vec[i].second + 1 << " " << it->second + 1 << ln;
        return 0;
    }   
    cout << "IMPOSSIBLE" << ln;
    return 0;
}
