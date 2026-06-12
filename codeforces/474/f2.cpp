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

int main(){
    _;

    ll n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (ll k = 0; k < n; k++) cin >> a[k];

    while (q--) {
        int t; ll l, r;
        cin >> t >> l >> r;
        l--; r--; 

        if (t == 1) {
            for (ll k = l; k <= r; k++) a[k] ^= 1;
        } else {
            ll best = 0, cur = 0;
            for (ll k = l; k <= r; k++) {
                if (a[k] == 1) { cur++; best = max(best, cur); }
                else cur = 0;
            }
            cout << best << "\n";
        }
    }
    return 0;
}