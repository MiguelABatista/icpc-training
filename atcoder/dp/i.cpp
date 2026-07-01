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
    ll n; cin >> n;
    vector<ld> p(n), f(n+1);
    forn(i,0,n) cin >> p[i];
    f[0] = 1;
    forn(i,0,n){
        for(ll j = n; j>= 0; j--){
            f[j] = (1-p[i])*f[j] + p[i]*(j == 0 ? 0 : f[j-1]);
        }
        debugv(f);
    }    

    ld resp = 0;
    forn(i,(n+1)/2, n+1) resp += f[i];
    cout << fixed << setprecision(10) << resp << ln;
    return 0;
}
