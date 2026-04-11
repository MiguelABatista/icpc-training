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
const ll MAX = 1'000'000'000'005ll;

inline ll tri(ll n){
    return (n*(n+1))/2;
}
int main() {
    _;
    v64 s(sqrt(2*MAX) + 10, INF);

    forn(i,0,MAX){
        if(tri(i) >= MAX) break;
        s[i] = tri(i);
    }

    ll t; cin >> t;

    forn(xx,0,t){
        ll n; cin >> n;

        bool b = false;
        forn(i,-1,n){
            if(tri(i) > n) break;
            ll tar = n-tri(i);
            auto it = lower_bound(s.begin(), s.end(), tar);
            if(*it == tar){
                if(i == -1) cout << 1 << ln;
                else cout << 2 << ln;
                b = true;
                break;
            } 
        }
        if(b) continue;
        cout << 3 << ln;
    }
    return 0;
}
