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

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];
    sort(vec.begin(), vec.end());

    ll resp = INF;
    forn(i,0,n-1){
        ll lb = vec[i+1] + vec[i];
        ll t1 = n - (lower_bound(vec.begin(), vec.end(), lb) - vec.begin());
        debug(i);
        debug(t1);
        debug(lb);
        trace(cout << ln;);
        resp = min(t1 + i, resp);
    }

    cout << resp << ln;
    trace(cout << "------------\n\n");
}

int main() {
    _;
    ll t; cin >> t; 
    while(t--) solve();

    return 0;
}
