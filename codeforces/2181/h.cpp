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
    ll w, h, d; cin >> w >> h >> d;
    ll n; cin >> n;

    ll w1 = gcd(n,w);
    n /= w1;
    ll h1 = gcd(n,h);
    n /= h1;
    ll d1 = gcd(n,d);
    n /= d1;
    if(n != 1){
        cout << -1 << ln;
    }else{
        cout << w1-1 << " " << h1-1 << " " << d1-1 << ln;
    }
    return 0;
}
