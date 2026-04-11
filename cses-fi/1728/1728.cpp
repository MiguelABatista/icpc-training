#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double ld;
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
const ll ep = 0.000'000'01;

int main() {
    _;
    ll n; cin >>  n;
    v64 r(n);
    forn(i,0,n) cin >> r[i];
    ld resp = 0;
    forn(i,0,n){
        forn(j,i+1,n){
            ll cnt = 0;
            forn(x,1,r[i]+1){
                forn(y,1,r[j]+1){
                    if(x > y) cnt++;
                }
            }
            resp += ld(cnt)/(r[i]*r[j]);
        }
    }


    cout << fixed << setprecision(6) << resp << ln;
    ld resp2 = roundeven((resp)*ld(1e6))/ld(1e6);
    cout << fixed << setprecision(6) << resp2 << ln;
    return 0;
}
