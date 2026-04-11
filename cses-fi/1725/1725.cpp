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
    ll n, a, b; cin >> n >> a >> b;
    vector<vector<ld>> f(2, vector<ld>(6*n+1));
    ll k = 0;
    f[k][0] = 1;

    forn(i,0,n){
        for(ll j = 6*n; j>= 0; j--){
            f[k^1][j] = 0;
            forn(l,1,7){
                if(j-l < 0) continue;
                f[k^1][j] += f[k][j-l]*(ld(1)/6);
            }
        }
        k ^= 1;
    }
    debugv(f[k]);
    ld tot = 0;
    forn(i,a,b+1) tot += f[k][i];
    cout << fixed << setprecision(6) << tot << ln;
    return 0;
}
