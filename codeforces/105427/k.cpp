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

bool ask(ll x){
    cout << "buf[" << x << "]" << endl;
    ll y; cin >> y;
    return (y == 0);
}

int main() {
    // _;
    ll pot = 2;
    while(!ask(pot)) pot *= 2;
    ll l = pot/2;
    ll r = pot-1;
    ll ans = l;
    debug(pot);
    while(l <= r){
        ll m = (l+r)/2;
        if(ask(m)){
            r = m - 1;
        }else{
            ans = m;
            l = m + 1;
        }
    }
    cout << "strlen(buf) = " << ans+1 << endl;
    return 0;
}
