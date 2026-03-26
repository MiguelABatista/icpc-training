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
    v64 vec = {1, 3, 4 , 5, 11, 13};

    ll l = 0;
    ll r = vec.size() - 1;
    ll target;
    cin >> target;
    ll ans = r;
    while(l <= r){
        ll mid = (l+r)/2;
        if(vec[mid] > target){
            r = mid - 1;
            ans = mid;
        }
        if(vec[mid] < target){
            l  = mid +1;
        }
        if(vec[mid] == target){
            ans = mid;
            cout << mid << ln;
            return 0;
        }
    }
    cout << ans << ln;
    return 0;
}
