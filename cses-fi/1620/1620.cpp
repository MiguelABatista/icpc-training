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
    ll n, t; cin >> n >> t;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];

    ll l = 0;
    ll r = INF;
    ll ans = INF;

    auto test = [&](ll val){
        ll s = 0;
        forn(i,0,n){
            s += val/vec[i];
            if(s >= t) return true;
        }
        return false;
    };

    while(l <= r){
        ll m = (l+r)/2;
        if(test(m)){
            ans = m;
            r = m-1;
        }else{
            l = m+1;
        }
    }

    cout << ans << ln;
    return 0;
}
