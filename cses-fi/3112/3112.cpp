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
ll cnt = 0;

bool ask(ll y){
    assert(cnt < 30);
    cnt++;
    // cout << cnt << ln;
    cout << "? " << y << endl;
    string s; cin >> s;
    return (s[0] == 'Y');
}

int main() {
    _;
    ll l = 1;
    ll r = 1'000'000'000;
    ll ans = 1;
    while(l <= r){
        ll m = (l+r)/2;
        bool b = ask(m);
        if(b){
            l = m+1;
            ans = m+1;
        }else{
            r = m-1;
        }
    }
    cout << "! " << ans << endl;
    return 0;
}
