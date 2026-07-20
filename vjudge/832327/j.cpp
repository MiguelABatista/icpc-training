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
const ll MAX = 20'000'005;

bool test(multiset<ll> s, ll b, ll m){
    ll cnt = 0;
    while(sz(s) > 0){
        auto it = s.begin();
        ll x = (-1)* (*it);
        s.erase(it);
        if(x > b) return false;
        cnt++;
        if(sz(s) == 0) break;
        ll t = b - x;
        auto itt = s.lower_bound(-t);
        if(itt != s.end()){ 
            s.erase(itt);
        }
    }
    return (cnt <= m);
};

int main() {
    _;
    ll n, m; cin >> n >> m;
    vll vec(n); forn(i,0,n) cin >> vec[i];
    multiset<ll> s;
    forn(i,0,n) s.insert(-vec[i]);
    ll l = 0;
    ll r = MAX;
    ll ans = 0;
    while(l <= r){
        ll mid = (l+r)/2;
        debug(mid);
        debug(m);
        debugv(s);
        debug((test(s, mid, m)));
        trace(cout << ln;)
        if(test(s, mid, m)){
            ans = mid;
            r = mid-1;
        }else{
            l = mid+1;
        }
    }
    cout << ans << ln;
    return 0;
}
