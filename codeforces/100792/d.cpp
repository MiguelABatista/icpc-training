#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
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

int main() {
    _;
    ld t1, h1;
    ld t2, h2;
    cin >> h1 >> t1;
    cin >> h2 >> t2;

    ld sqh1 = sqrt(h1);
    ld sqh2 = sqrt(h2);
    
    ld d = abs((sqh1/(sqh2-sqh1))*(t2-t1) - t1);

    cout << fixed << setprecision(6) << d << ln;

    // ld g1 = (2*h1)/((t1+d)*(t1+d));
    // ld g2 = (2*h2)/((t2+d)*(t2+d));
    // ld g = (g1+g2)/2;

    // cout << fixed << setprecision(6) << g1 << ln;
    // cout << fixed << setprecision(6) << g2 << ln;
    // cout << fixed << setprecision(6) << g << ln;
    return 0;
}
