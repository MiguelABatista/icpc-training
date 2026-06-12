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

void solve(){
    ll n; cin >> n;
    vll c(n), p(n);
    forn(i,0,n) cin >> c[i] >> p[i];
    vll acc(n);
    double resp = 0;
    for(ll i = n-1; i>= 0; i--){
        debug(i);
        debug(resp);
        double aux = (1.0- ((double)p[i])/100.0);
        if(aux*resp + c[i] > resp){
            resp *= aux;
            resp += c[i];
        }
        debug(resp);
        trace(cout << "--------------\n\n";);
    }
    cout << fixed << setprecision(10) << resp << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
