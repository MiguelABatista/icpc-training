#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
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
    ll n, k; cin >> n >> k;
    vector<ld> f(k+1);
    forn(x,1,k+1){
        ld p = 1;
        forn(i,0,n){
            p *= ld(x)/k;
        }
        forn(i,0,x) p -= f[i];
        f[x] = p;
    }
    ld e = 0;
    forn(i,0,k+1) e += i*f[i];

    ld resp = roundeven(e*1e6)/1e6;
 
    cout << fixed << setprecision(6) << resp << ln;
    return 0;
}
