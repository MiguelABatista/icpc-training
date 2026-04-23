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
const ll MAXSQ = 1004;

int main() {
    _;ll n; cin >> n;

    vll sq(MAXSQ);
    forn(i, 0, MAXSQ) sq[i] = i*i;

    forn(i, 0, MAXSQ){
        ll target = n - sq[i];
        auto it = lower_bound(sq.begin(), sq.end(), target);
        if(target == *it){
            ll a = i, b = it - sq.begin();
            cout << 0 << " " << 0 << ln;
            cout << a << " " << b << ln;
            cout << a-b << " " << a+b << ln;
            cout << -b << " " << a << ln;

            break;
        }
    }

    cout << "IMPOSSIBLE" << ln;

    return 0;
}
