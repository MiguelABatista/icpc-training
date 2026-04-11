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
const ll MOD = 1'000'000'007;
const ll INV2 = 500'000'004;

ll sum(ll x){
    x %= MOD;
    return ((x*(x+1))/2)%MOD;
}

int main() {
    _;
    ll n; cin >> n;
    ll resp = 0;
    for (ll l = 1, r; l <= n; l = r + 1) {
        ll val = n / l;
        r = n / val;
        // n/i == val para todo i em [l, r]
        resp = (resp + ((sum(r) - sum(l-1) + MOD)%MOD * val)%MOD)%MOD;
    }
    cout << resp << ln;
    return 0;
}

// 1   2   3   4   5
// 1 + 3 + 4 + 7 + 6
// 1 + 1 + 1 + 1 + 1
//     2       2
//         3
//             4
//                 5