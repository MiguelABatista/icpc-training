#include <bits/stdc++.h>
#include <bits/stdc++.h>
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

int main() {
    _;
    ll m, n; cin >> m >> n;
    v64 s(m);
    v64 l(m);
    forn(i,0,m) cin >> s[i];
    forn(i,0,m) cin >> l[i];

    v64 dps(n);
    v64 dpl(n);

    dps[0] = s[0];
    dpl[0] = l[0];

    forn(i,1,n){
        ll resps = 0;
        ll respl = 0;
        forn(j,0,m){
            ll curr = (dps[i-1]*(s[j]+l[j]) + dpl[i-1]*s[j])%MOD; 
            resps = (resps + curr*s[j])%MOD;
            respl = (respl + curr*l[j])%MOD;
        }
        dps[i] = resps;
        dpl[i] = respl;
    }

    ll resp = 0;
    
    debugv(dps);
    debugv(dpl);

    forn(j,0,m){
        ll curr = (dps[n-1]*(s[j]+l[j]) + dpl[n-1]*s[j])%MOD; 
        resp = (resp + curr)%MOD;
    }

    cout << resp << ln;
    return 0;
}
